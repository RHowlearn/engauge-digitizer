/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentModelGridRemoval.h"
#include "EngaugeAssert.h"
#include "GridHealer.h"
#include "Logger.h"
#include <QImage>
#include <qmath.h>
#include <QRgb>
#include "TriangleFill.h"

GridHealer::GridHealer(const DocumentModelGridRemoval &modelGridRemoval) :
  m_modelGridRemoval (modelGridRemoval),
  m_verticalSeparation (0),
  m_horizontalSeparation (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridHealer::GridHealer";
}

void GridHealer::addAdjacentPoints (int x0,
                                    int y0,
                                    int x1,
                                    int y1)
{
  m_pairHalves0.push_back (QPoint (x0, y0));
  m_pairHalves1.push_back (QPoint (x1, y1));
}

void GridHealer::applyAdjacentPairs (const QImage &imageBeforeGridRemoval)
{
  QList<QPoint>::iterator itr0 = m_pairHalves0.begin();
  QList<QPoint>::iterator itr1 = m_pairHalves1.begin();

  while (itr0 != m_pairHalves0.end()) {

    QPoint p0 = *itr0;
    QPoint p1 = *itr1;

    double x0 = p0.x();
    double y0 = p0.y();
    double x1 = p1.x();
    double y1 = p1.y();

    if (x0 == x1) {

      // Line is horizontal so independent variable is x
      if (pixelIsBlack (imageBeforeGridRemoval, x0, y0)) {
        m_blackPixelsBelow [x0] = y0;
      }
      if (pixelIsBlack (imageBeforeGridRemoval, x1, y1)) {
        m_blackPixelsAbove [x1] = y1;
      }
      m_verticalSeparation = qAbs (y1 - y0);

    } else if (y0 == y1) {

      // Line is vertical so independent variable is  y
      if (pixelIsBlack (imageBeforeGridRemoval, x0, y0)) {
        m_blackPixelsLeft [y0] = x0;
      }
      if (pixelIsBlack (imageBeforeGridRemoval, x1, y1)) {
        m_blackPixelsRight [y1] = x1;
      }
      m_horizontalSeparation = qAbs (x1 - x0);

    } else {
      LOG4CPP_ERROR_S ((*mainCat)) << "Invalid case in GridHealer";
    }

    ++itr0;
    ++itr1;
  }
}

void GridHealer::doHealingHorizontal (QImage &image)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridHealer::doHealingHorizontal "
                              << " countBelow=" << m_blackPixelsBelow.count()
                              << " countAbove=" << m_blackPixelsAbove.count();

  // Algorithm requires at least one point in each of the lists
  if (m_blackPixelsBelow.count() > 0 &&
      m_blackPixelsAbove.count() > 0) {

    int xFirst = qMin (m_blackPixelsBelow.firstKey (),
                       m_blackPixelsAbove.firstKey ());
    int xLast = qMax (m_blackPixelsBelow.lastKey (),
                      m_blackPixelsAbove.lastKey ());

    // Right triangle with one edge crossing the gap (separation value) and hypotenuse giving
    // maximum point separation (closest distance) gives the maximum horizontal separation
    int maxHorSep = qSqrt (qPow (m_modelGridRemoval.closeDistance(), 2) -
                           qPow (m_verticalSeparation, 2));

    int xBelowSkipTo = 0; // Used by inner loop to skip to this iterator value

    for (int xBelowStart = xFirst; xBelowStart <= xLast; xBelowStart++) {
      if ((xBelowSkipTo < xBelowStart) && m_blackPixelsBelow.contains (xBelowStart)) {
        // This could be the start of a new trapezoid. Find where the range on the same side ends
        int xBelowOutOfBounds = xLast + 1; // Value forcing transition to out of range
        for (int xBelowEnd = xBelowStart + 1; xBelowEnd <= xBelowOutOfBounds; xBelowEnd++) {

          if (xBelowSkipTo > xBelowStart) {
            break; // Pop this iteration level
          }

          if ((xBelowSkipTo < xBelowEnd) && (!m_blackPixelsBelow.contains (xBelowEnd) || (xBelowEnd == xBelowOutOfBounds))) {

            // Below range goes from xBelowStart (inclusive) to xBelowEnd (exclusive). There could
            // be zero, one or more above ranges that overlap within maxHorSep, corresponding
            // to an equal number of trapezoids to be filled in
            //
            // It is important to note that every above point between xBelowStart-maxHorSep to
            // xBelowEnd+maxHorSep is close enough (<close distance) to a point in the below range
            bool insideRange = false; // Trivial state machine which targets transitions into/out of ranges
            int xAboveStartForThisRange = 0;
            int xAboveOutOfBounds = xBelowEnd + maxHorSep + 1; // Value forcing transition to out of range
            for (int xAbove = xBelowStart - maxHorSep; xAbove <= xAboveOutOfBounds; xAbove++) {

              bool includePixel = m_blackPixelsAbove.contains (xAbove) && (xAbove < xAboveOutOfBounds);

              if (!insideRange && includePixel) {
                // Transition from outside range to inside range
                insideRange = true;
                xAboveStartForThisRange = xAbove;
              } else if (insideRange && !includePixel) {
                // Transition from inside range to outside range
                insideRange = false;
                int xAboveEndForThisRange = xAbove - 1;
                int xBelowStartForThisRange = qMax (xBelowStart, xAboveStartForThisRange - maxHorSep);
                int xBelowEndForThisRange = qMin (xBelowEnd - 1, xAboveEndForThisRange + maxHorSep);

                // Four points that define the trapezoid to be filled in
                fillTrapezoid (image,
                               xBelowStartForThisRange, m_blackPixelsBelow [xBelowStartForThisRange],
                               xBelowEndForThisRange,   m_blackPixelsBelow [xBelowEndForThisRange  ],
                               xAboveEndForThisRange,   m_blackPixelsAbove [xAboveEndForThisRange  ],
                               xAboveStartForThisRange, m_blackPixelsAbove [xAboveStartForThisRange]);
              }
            }

            // Make outer loop skip already-processed xBelowStart values
            xBelowSkipTo = xBelowEnd + 1;
          }
        }
      }
    }
  }
}

void GridHealer::doHealingVertical (QImage &image)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridHealer::doHealingVertical "
                              << " countLeft=" << m_blackPixelsLeft.count()
                              << " countRight=" << m_blackPixelsRight.count();

  // Algorithm requires at least one point in each of the lists
  if (m_blackPixelsLeft.count() > 0 &&
      m_blackPixelsRight.count() > 0) {

    int yFirst = qMin (m_blackPixelsLeft.firstKey (),
                       m_blackPixelsRight.firstKey ());
    int yLast = qMax (m_blackPixelsLeft.lastKey (),
                      m_blackPixelsRight.lastKey ());

    // Right triangle with one edge crossing the gap (separation value) and hypotenuse giving
    // maximum point separation (closest distance) gives the maximum vertical separation
    int maxVerSep = qSqrt (qPow (m_modelGridRemoval.closeDistance(), 2) -
                           qPow (m_horizontalSeparation, 2));

    int yLeftSkipTo = 0; // Used by inner loop to skip to this iterator value

    for (int yLeftStart = yFirst; yLeftStart <= yLast; yLeftStart++) {
      if ((yLeftSkipTo < yLeftStart) && m_blackPixelsLeft.contains (yLeftStart)) {
        // This could be the start of a new trapezoid. Find where the range on the same side ends
        int yLeftOutOfBounds = yLast + 1; // Value forcing transition to out of range
        for (int yLeftEnd = yLeftStart + 1; yLeftEnd <= yLeftOutOfBounds; yLeftEnd++) {

          if (yLeftSkipTo > yLeftStart) {
            break; // Pop this iteration level
          }

          if ((yLeftSkipTo < yLeftEnd) && (!m_blackPixelsLeft.contains (yLeftEnd) || (yLeftEnd == yLeftOutOfBounds))) {

            // Left range goes from yLeftStart (inclusive) to yLeftEnd (exclusive). There could
            // be zero, one or more right ranges that overlap within maxVerSep, corresponding
            // to an equal number of trapezoids to be filled in
            //
            // It is important to note that every right point between yLeftStart-maxVerSep to
            // yLeftEnd+maxVerSep is close enough (<close distance) to a point in the left range
            bool insideRange = false; // Trivial state machine which targets transitions into/out of ranges
            int yRightStartForThisRange = 0;
            int yRightOutOfBounds = yLeftEnd + maxVerSep + 1; // Value forcing transition to out of range
            for (int yRight = yLeftStart - maxVerSep; yRight <= yRightOutOfBounds; yRight++) {

              bool includePixel = m_blackPixelsRight.contains (yRight) && (yRight < yRightOutOfBounds);

              if (!insideRange && includePixel) {
                // Transition from outside range to inside range
                insideRange = true;
                yRightStartForThisRange = yRight;
              } else if (insideRange && !includePixel) {
                // Transition from inside range to outside range
                insideRange = false;
                int yRightEndForThisRange = yRight - 1;
                int yLeftStartForThisRange = qMax (yLeftStart, yRightStartForThisRange - maxVerSep);
                int yLeftEndForThisRange = qMin (yLeftEnd - 1, yRightEndForThisRange + maxVerSep);

                // Four points that define the trapezoid to be filled in
                fillTrapezoid (image,
                               m_blackPixelsLeft  [yLeftStartForThisRange ], yLeftStartForThisRange,
                               m_blackPixelsRight [yRightStartForThisRange], yRightStartForThisRange,
                               m_blackPixelsRight [yRightEndForThisRange  ], yRightEndForThisRange,
                               m_blackPixelsLeft  [yLeftEndForThisRange   ], yLeftEndForThisRange);
              }
            }

            // Make outer loop skip already-processed yLeftStart values
            yLeftSkipTo = yLeftEnd + 1;
          }
        }
      }
    }
  }
}

void GridHealer::fillTrapezoid (QImage &image,
                                int xBL, int yBL,
                                int xBR, int yBR,
                                int xTR, int yTR,
                                int xTL, int yTL)
{
  // Any quadrilateral (including this trapezoid) can be considered the union of two triangles
  TriangleFill triangleFill;
  triangleFill.fill (image,
                     QPoint (xBL, yBL),
                     QPoint (xBR, yBR),
                     QPoint (xTR, yTR));
  triangleFill.fill (image,
                     QPoint (xBL, yBL),
                     QPoint (xTL, yTL),
                     QPoint (xTR, yTR));
}

QImage GridHealer::healed (const QImage &imageAfterGridRemoval)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridHealer::healed";

  applyAdjacentPairs (imageAfterGridRemoval);

  QImage image (imageAfterGridRemoval);

  doHealingHorizontal (image);
  doHealingVertical (image);

  return image;
}

bool GridHealer::pixelIsBlack (const QImage &image,
                               int x,
                               int y) const
{
  QRgb rgb = image.pixel (x, y);
  return qGray (rgb) < 128;
}
