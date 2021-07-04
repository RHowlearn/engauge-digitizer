/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentSerialize.h"

const QString DOCUMENT_SERIALIZE_APPLICATION ("Application");
const QString DOCUMENT_SERIALIZE_APPLICATION_VERSION_NUMBER ("VersionNumber");
const QString DOCUMENT_SERIALIZE_AXES_CHECKER ("AxesChecker");
const QString DOCUMENT_SERIALIZE_AXES_CHECKER_LINE_COLOR ("LineColor");
const QString DOCUMENT_SERIALIZE_AXES_CHECKER_MODE ("Mode");
const QString DOCUMENT_SERIALIZE_AXES_CHECKER_SECONDS ("Seconds");
const QString DOCUMENT_SERIALIZE_AXES_POINTS_REQUIRED ("AxesPointsRequired");
const QString DOCUMENT_SERIALIZE_BOOL_FALSE ("False");
const QString DOCUMENT_SERIALIZE_BOOL_TRUE ("True");
const QString DOCUMENT_SERIALIZE_CMD ("Cmd");
const QString DOCUMENT_SERIALIZE_CMD_ADD_POINT_AXIS ("CmdAddPointAxis");
const QString DOCUMENT_SERIALIZE_CMD_ADD_POINT_GRAPH ("CmdAddPointGraph");
const QString DOCUMENT_SERIALIZE_CMD_ADD_POINTS_GRAPH ("CmdAddPointsGraph");
const QString DOCUMENT_SERIALIZE_CMD_ADD_SCALE ("CmdAddScale");
const QString DOCUMENT_SERIALIZE_CMD_COPY ("CmdCopy");
const QString DOCUMENT_SERIALIZE_CMD_CUT ("CmdCut");
const QString DOCUMENT_SERIALIZE_CMD_DELETE ("CmdDelete");
const QString DOCUMENT_SERIALIZE_CMD_DELETE_ADDED_POINTS ("AddedPoints");
const QString DOCUMENT_SERIALIZE_CMD_DESCRIPTION ("Description");
const QString DOCUMENT_SERIALIZE_CMD_EDIT_POINT_AXIS ("CmdEditPointAxis");
const QString DOCUMENT_SERIALIZE_CMD_EDIT_POINT_GRAPH ("CmdEditPointGraph");
const QString DOCUMENT_SERIALIZE_CMD_GONG ("CmdGong");
const QString DOCUMENT_SERIALIZE_CMD_GUIDELINE_ADD_X_T ("CmdGuidelineAddXT");
const QString DOCUMENT_SERIALIZE_CMD_GUIDELINE_ADD_Y_R ("CmdGuidelineAddYR");
const QString DOCUMENT_SERIALIZE_CMD_GUIDELINE_MOVE_X_T ("CmdGuidelineMoveXT");
const QString DOCUMENT_SERIALIZE_CMD_GUIDELINE_MOVE_Y_R ("CmdGuidelineMoveYR");
const QString DOCUMENT_SERIALIZE_CMD_GUIDELINE_REMOVE_X_T ("CmdGuidelineRemoveXT");
const QString DOCUMENT_SERIALIZE_CMD_GUIDELINE_REMOVE_Y_R ("CmdGuidelineRemoveYR");
const QString DOCUMENT_SERIALIZE_CMD_MEDIATOR ("CmdMediator");
const QString DOCUMENT_SERIALIZE_CMD_MOVE_BY ("CmdMoveBy");
const QString DOCUMENT_SERIALIZE_CMD_REDO_FOR_TEST ("CmdRedoForTest");
const QString DOCUMENT_SERIALIZE_CMD_SELECT_COORD_SYSTEM ("CmdSelectCoordSystem");
const QString DOCUMENT_SERIALIZE_CMD_SETTINGS_AXES_CHECKER ("CmdSettingsAxesChecker");
const QString DOCUMENT_SERIALIZE_CMD_SETTINGS_COLOR_FILTER ("CmdSettingsColorFilter");
const QString DOCUMENT_SERIALIZE_CMD_SETTINGS_COORDS ("CmdSettingsCoords");
const QString DOCUMENT_SERIALIZE_CMD_SETTINGS_CURVE_LIST ("CmdSettingsCurveAddRemove"); // AddRemove versus List for old dig files
const QString DOCUMENT_SERIALIZE_CMD_SETTINGS_CURVE_PROPERTIES ("CmdSettingsCurveProperties");
const QString DOCUMENT_SERIALIZE_CMD_SETTINGS_DIGITIZE_CURVE ("CmdSettingsDigitizeCurve");
const QString DOCUMENT_SERIALIZE_CMD_SETTINGS_EXPORT ("CmdSettingsExport");
const QString DOCUMENT_SERIALIZE_CMD_SETTINGS_GENERAL ("CmdSettingsGeneral");
const QString DOCUMENT_SERIALIZE_CMD_SETTINGS_GRID_DISPLAY ("CmdSettingsGridDisplay");
const QString DOCUMENT_SERIALIZE_CMD_SETTINGS_GRID_REMOVAL ("CmdSettingsGridRemoval");
const QString DOCUMENT_SERIALIZE_CMD_SETTINGS_GUIDELINE ("CmdSettingsGuideline");
const QString DOCUMENT_SERIALIZE_CMD_SETTINGS_POINT_MATCH ("CmdSettingsPointMatch");
const QString DOCUMENT_SERIALIZE_CMD_SETTINGS_SEGMENTS ("CmdSettingsSegments");
const QString DOCUMENT_SERIALIZE_CMD_TYPE ("Type");
const QString DOCUMENT_SERIALIZE_CMD_UNDO_FOR_TEST ("CmdUndoForTest");
const QString DOCUMENT_SERIALIZE_COLOR_FILTER ("ColorFilter");
const QString DOCUMENT_SERIALIZE_COLOR_FILTER_FOREGROUND_HIGH ("ForegroundHigh");
const QString DOCUMENT_SERIALIZE_COLOR_FILTER_FOREGROUND_LOW ("ForegroundLow");
const QString DOCUMENT_SERIALIZE_COLOR_FILTER_HUE_HIGH ("HueHigh");
const QString DOCUMENT_SERIALIZE_COLOR_FILTER_HUE_LOW ("HueLow");
const QString DOCUMENT_SERIALIZE_COLOR_FILTER_INTENSITY_HIGH ("IntensityHigh");
const QString DOCUMENT_SERIALIZE_COLOR_FILTER_INTENSITY_LOW ("IntensityLow");
const QString DOCUMENT_SERIALIZE_COLOR_FILTER_MODE ("Mode");
const QString DOCUMENT_SERIALIZE_COLOR_FILTER_MODE_STRING ("ModeString");
const QString DOCUMENT_SERIALIZE_COLOR_FILTER_SATURATION_HIGH ("SaturationHigh");
const QString DOCUMENT_SERIALIZE_COLOR_FILTER_SATURATION_LOW ("SaturationLow");
const QString DOCUMENT_SERIALIZE_COLOR_FILTER_VALUE_HIGH ("ValueHigh");
const QString DOCUMENT_SERIALIZE_COLOR_FILTER_VALUE_LOW ("ValueLow");
const QString DOCUMENT_SERIALIZE_COMMON ("Common"); // Replaced by DOCUMENT_SERIALIZE_GENERAL but kept for backwards compatibility
const QString DOCUMENT_SERIALIZE_COORD_SYSTEM ("CoordSystem");
const QString DOCUMENT_SERIALIZE_COORD_SYSTEM_INDEX_AFTER ("CoordSystemIndexAfter");
const QString DOCUMENT_SERIALIZE_COORD_SYSTEM_INDEX_BEFORE ("CoordSystemIndexBefore");
const QString DOCUMENT_SERIALIZE_COORDS ("Coords");
const QString DOCUMENT_SERIALIZE_COORDS_ORIGIN_RADIUS ("Coords");
const QString DOCUMENT_SERIALIZE_COORDS_SCALE_X_THETA ("ScaleXTheta");
const QString DOCUMENT_SERIALIZE_COORDS_SCALE_X_THETA_STRING ("ScaleXThetaString");
const QString DOCUMENT_SERIALIZE_COORDS_SCALE_Y_RADIUS ("ScaleYRadius");
const QString DOCUMENT_SERIALIZE_COORDS_SCALE_Y_RADIUS_STRING ("ScaleYRadiusString");
const QString DOCUMENT_SERIALIZE_COORDS_TYPE ("Type");
const QString DOCUMENT_SERIALIZE_COORDS_TYPE_STRING ("TypeString");
const QString DOCUMENT_SERIALIZE_COORDS_UNITS_DATE ("UnitsDate");
const QString DOCUMENT_SERIALIZE_COORDS_UNITS_DATE_STRING ("UnitsDateString");
const QString DOCUMENT_SERIALIZE_COORDS_UNITS_RADIUS ("UnitsRadius");
const QString DOCUMENT_SERIALIZE_COORDS_UNITS_RADIUS_STRING ("UnitsRadiusString");
const QString DOCUMENT_SERIALIZE_COORDS_UNITS_THETA ("UnitsTheta");
const QString DOCUMENT_SERIALIZE_COORDS_UNITS_THETA_STRING ("UnitsThetaString");
const QString DOCUMENT_SERIALIZE_COORDS_UNITS_TIME ("UnitsTime");
const QString DOCUMENT_SERIALIZE_COORDS_UNITS_TIME_STRING ("UnitsTimeString");
const QString DOCUMENT_SERIALIZE_COORDS_UNITS_X ("UnitsX");
const QString DOCUMENT_SERIALIZE_COORDS_UNITS_X_STRING ("UnitsXString");
const QString DOCUMENT_SERIALIZE_COORDS_UNITS_Y ("UnitsY");
const QString DOCUMENT_SERIALIZE_COORDS_UNITS_Y_STRING ("UnitsYString");
const QString DOCUMENT_SERIALIZE_COPIED ("Copied");
const QString DOCUMENT_SERIALIZE_CSV ("Csv");
const QString DOCUMENT_SERIALIZE_CURVE ("Curve");
const QString DOCUMENT_SERIALIZE_CURVE_NAME ("CurveName");
const QString DOCUMENT_SERIALIZE_CURVE_POINTS ("CurvePoints");
const QString DOCUMENT_SERIALIZE_CURVES_ENTRY ("CurvesEntry");
const QString DOCUMENT_SERIALIZE_CURVES_ENTRY_CURVE_NAME_CURRENT ("CurveNameCurrent");
const QString DOCUMENT_SERIALIZE_CURVES_ENTRY_CURVE_NAME_ORIGINAL ("CurveNameOriginal");
const QString DOCUMENT_SERIALIZE_CURVES_ENTRY_NUM_POINTS ("NumPoints");
const QString DOCUMENT_SERIALIZE_CURVES_GRAPHS ("CurvesGraphs");
const QString DOCUMENT_SERIALIZE_CURVE_STYLE ("CurveStyle");
const QString DOCUMENT_SERIALIZE_CURVE_STYLES ("CurveStyles");
const QString DOCUMENT_SERIALIZE_DIGITIZE_CURVE ("DigitizeCurve");
const QString DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_INNER_RADIUS ("CursorInnerRadius");
const QString DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_LINE_WIDTH ("CursorLineWidth");
const QString DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_SIZE ("CursorSize");
const QString DOCUMENT_SERIALIZE_DIGITIZE_CURVE_CURSOR_STANDARD_CROSS ("CursorStandardCross");
const QString DOCUMENT_SERIALIZE_DIGITIZE_STATE ("DigitizeState");
const QString DOCUMENT_SERIALIZE_DIGITIZE_STATE_STRING ("DigitizeStateString");
const QString DOCUMENT_SERIALIZE_DOCUMENT ("Document");
const QString DOCUMENT_SERIALIZE_EDIT_GRAPH_IDENTIFIERS ("Identifiers");
const QString DOCUMENT_SERIALIZE_EDIT_GRAPH_IS_X ("IsX");
const QString DOCUMENT_SERIALIZE_EDIT_GRAPH_IS_Y ("IsY");
const QString DOCUMENT_SERIALIZE_EDIT_GRAPH_X ("X");
const QString DOCUMENT_SERIALIZE_EDIT_GRAPH_Y ("Y");
const QString DOCUMENT_SERIALIZE_ERROR ("Error");
const QString DOCUMENT_SERIALIZE_ERROR_COMMENT ("Comment");
const QString DOCUMENT_SERIALIZE_ERROR_CONTEXT ("Context");
const QString DOCUMENT_SERIALIZE_ERROR_FILE ("File");
const QString DOCUMENT_SERIALIZE_ERROR_LINE ("Line");
const QString DOCUMENT_SERIALIZE_ERROR_REPORT ("ErrorReport"); // Treated same as DOCUMENT_SERIALIZE_DOCUMENT
const QString DOCUMENT_SERIALIZE_EXPORT ("Export");
const QString DOCUMENT_SERIALIZE_EXPORT_CURVE_NAME_NOT_EXPORTED ("CurveNameNotExported");
const QString DOCUMENT_SERIALIZE_EXPORT_CURVE_NAME_NOT_EXPORTED_NAME ("CurveNameNotSupportedName");
const QString DOCUMENT_SERIALIZE_EXPORT_CURVE_NAMES_NOT_EXPORTED ("CurveNamesNotExported");
const QString DOCUMENT_SERIALIZE_EXPORT_DELIMITER ("Delimiter");
const QString DOCUMENT_SERIALIZE_EXPORT_DELIMITER_OVERRIDE_CSV_TSV ("OverrideCsvTsv");
const QString DOCUMENT_SERIALIZE_EXPORT_DELIMITER_STRING ("DelimiterString");
const QString DOCUMENT_SERIALIZE_EXPORT_EXTRAPOLATE_OUTSIDE_ENDPOINTS ("ExtrapolateOutsideEndpoints");
const QString DOCUMENT_SERIALIZE_EXPORT_HEADER ("Header");
const QString DOCUMENT_SERIALIZE_EXPORT_HEADER_STRING ("HeaderString");
const QString DOCUMENT_SERIALIZE_EXPORT_LAYOUT_FUNCTIONS ("LayoutFunctions");
const QString DOCUMENT_SERIALIZE_EXPORT_LAYOUT_FUNCTIONS_STRING ("LayoutFunctionsString");
const QString DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_FUNCTIONS ("PointsIntervalFunctions");
const QString DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_RELATIONS ("PointsIntervalRelations");
const QString DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_UNITS_FUNCTIONS ("PointsIntervalUnitsFunctions");
const QString DOCUMENT_SERIALIZE_EXPORT_POINTS_INTERVAL_UNITS_RELATIONS ("PointsIntervalUnitsRelations");
const QString DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_FUNCTIONS ("PointsSelectionFunctions");
const QString DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_FUNCTIONS_STRING ("PointsSelectionFunctionsString");
const QString DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_RELATIONS ("PointsSelectionRelations");
const QString DOCUMENT_SERIALIZE_EXPORT_POINTS_SELECTION_RELATIONS_STRING ("PointsSelectionRelationsString");
const QString DOCUMENT_SERIALIZE_EXPORT_X_LABEL ("XLabel");
const QString DOCUMENT_SERIALIZE_FILE ("File");
const QString DOCUMENT_SERIALIZE_FILE_IMPORTED ("Imported");
const QString DOCUMENT_SERIALIZE_FILTER ("Filter");
const QString DOCUMENT_SERIALIZE_GENERAL ("General");
const QString DOCUMENT_SERIALIZE_GENERAL_CURSOR_SIZE ("CursorSize");
const QString DOCUMENT_SERIALIZE_GENERAL_EXTRA_PRECISION ("ExtraPrecision");
const QString DOCUMENT_SERIALIZE_GENERAL_ZOOM_CONTROL ("ZoomControl");
const QString DOCUMENT_SERIALIZE_GRAPH_AFTER ("GraphAfter");
const QString DOCUMENT_SERIALIZE_GRAPH_BEFORE ("GraphBefore");
const QString DOCUMENT_SERIALIZE_GRAPH_X ("GraphX");
const QString DOCUMENT_SERIALIZE_GRAPH_X_AFTER ("GraphXAfter");
const QString DOCUMENT_SERIALIZE_GRAPH_X_BEFORE ("GraphXBefore");
const QString DOCUMENT_SERIALIZE_GRAPH_Y ("GraphY");
const QString DOCUMENT_SERIALIZE_GRAPH_Y_AFTER ("GraphYAfter");
const QString DOCUMENT_SERIALIZE_GRAPH_Y_BEFORE ("GraphYBefore");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY ("GridDisplay");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_COLOR ("Color");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_COLOR_STRING ("ColorString");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_X ("CountX");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_COUNT_Y ("CountY");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_X ("DisableX");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_DISABLE_Y ("DisableY");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_LINE_WIDTH ("LineWidth");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_STABLE ("Stable");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_START_X ("StartX");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_START_Y ("StartY");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_X ("StepX");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_STEP_Y ("StepY");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_X ("StopX");
const QString DOCUMENT_SERIALIZE_GRID_DISPLAY_STOP_Y ("StopY");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL ("GridRemoval");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_CLOSE_DISTANCE ("CloseDistance");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_X ("CoordDisableX");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_X_STRING ("CoordDisableXString");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_Y ("CoordDisableY");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_COORD_DISABLE_Y_STRING ("CoordDisableYString");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_COUNT_X ("CountX");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_COUNT_Y ("CountY");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_DEFINED_GRID_LINES ("DefinedGridLines");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_STABLE ("Stable");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_START_X ("StartX");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_START_Y ("StartY");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_STEP_X ("StepX");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_STEP_Y ("StepY");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_STOP_X ("StopX");
const QString DOCUMENT_SERIALIZE_GRID_REMOVAL_STOP_Y ("StopY");
const QString DOCUMENT_SERIALIZE_GUIDELINE ("Guideline");
const QString DOCUMENT_SERIALIZE_GUIDELINE_CREATION_CIRCLE_RADIUS ("CreationCircleRadius");
const QString DOCUMENT_SERIALIZE_GUIDELINE_IDENTIFIER ("GuidelineIdentifier");
const QString DOCUMENT_SERIALIZE_GUIDELINE_LINE_COLOR ("LineColor");
const QString DOCUMENT_SERIALIZE_GUIDELINE_LINE_COLOR_STRING ("LineColorString");
const QString DOCUMENT_SERIALIZE_GUIDELINE_LINE_WIDTH_ACTIVE ("LineWidthActive");
const QString DOCUMENT_SERIALIZE_GUIDELINE_LINE_WIDTH_INACTIVE ("LineWidthInactive");
const QString DOCUMENT_SERIALIZE_GUIDELINES ("Guidelines");
const QString DOCUMENT_SERIALIZE_GUIDELINES_X ("GuidelinesX");
const QString DOCUMENT_SERIALIZE_GUIDELINES_Y ("GuidelinesY");
const QString DOCUMENT_SERIALIZE_GUIDELINE_VALUE ("GuidelineValue");
const QString DOCUMENT_SERIALIZE_HTML ("Html");
const QString DOCUMENT_SERIALIZE_IDENTIFIER ("Identifier");
const QString DOCUMENT_SERIALIZE_IDENTIFIER1 ("Identifier1");
const QString DOCUMENT_SERIALIZE_IDENTIFIER_NAME ("IdentifierName");
const QString DOCUMENT_SERIALIZE_IDENTIFIERS ("Identifiers");
const QString DOCUMENT_SERIALIZE_IMAGE ("Image");
const QString DOCUMENT_SERIALIZE_IMAGE_HEIGHT ("Height");
const QString DOCUMENT_SERIALIZE_IMAGE_WIDTH ("Width");
const QString DOCUMENT_SERIALIZE_LINE_STYLE ("LineStyle");
const QString DOCUMENT_SERIALIZE_LINE_STYLE_COLOR ("Color");
const QString DOCUMENT_SERIALIZE_LINE_STYLE_COLOR_STRING ("ColorString");
const QString DOCUMENT_SERIALIZE_LINE_STYLE_CONNECT_AS ("ConnectAs");
const QString DOCUMENT_SERIALIZE_LINE_STYLE_CONNECT_AS_STRING ("ConnectAsString");
const QString DOCUMENT_SERIALIZE_LINE_STYLE_CURVE_NAME ("CurveName");
const QString DOCUMENT_SERIALIZE_LINE_STYLE_WIDTH ("Width");
const QString DOCUMENT_SERIALIZE_LOAD_VIEWS ("LoadViews");
const QString DOCUMENT_SERIALIZE_LOAD_VIEWS_GRIDLINES ("LoadViewsGridlines");
const QString DOCUMENT_SERIALIZE_LOAD_VIEWS_GUIDELINES ("LoadViewsGuidelines");
const QString DOCUMENT_SERIALIZE_MAIN_WINDOW ("MainWindow");
const QString DOCUMENT_SERIALIZE_MOVED ("Moved");
const QString DOCUMENT_SERIALIZE_OPERATING_SYSTEM ("OperatingSystem");
const QString DOCUMENT_SERIALIZE_OPERATING_SYSTEM_ENDIAN ("Endian");
const QString DOCUMENT_SERIALIZE_OPERATING_SYSTEM_WORD_SIZE ("WordSize");
const QString DOCUMENT_SERIALIZE_ORDINAL ("Ordinal");
const QString DOCUMENT_SERIALIZE_ORDINAL1 ("Ordinal1");
const QString DOCUMENT_SERIALIZE_POINT ("Point");
const QString DOCUMENT_SERIALIZE_POINT_IDENTIFIER ("Identifier");
const QString DOCUMENT_SERIALIZE_POINT_IDENTIFIER_INDEX ("Index");
const QString DOCUMENT_SERIALIZE_POINT_IDENTIFIER_NAME ("Name");
const QString DOCUMENT_SERIALIZE_POINT_IDENTIFIERS ("Identifiers");
const QString DOCUMENT_SERIALIZE_POINT_IDENTIFIER_VALUE ("Value");
const QString DOCUMENT_SERIALIZE_POINT_IS_AXIS_POINT ("IsAxisPoint");
const QString DOCUMENT_SERIALIZE_POINT_IS_X_ONLY ("IsXOnly");
const QString DOCUMENT_SERIALIZE_POINT_MATCH ("PointMatch");
const QString DOCUMENT_SERIALIZE_POINT_MATCH_POINT_SIZE ("PointSize");
const QString DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_ACCEPTED ("ColorAccepted");
const QString DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_ACCEPTED_STRING ("ColorAcceptedString");
const QString DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_CANDIDATE ("ColorCandidate");
const QString DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_CANDIDATE_STRING ("ColorCandidateString");
const QString DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_REJECTED ("ColorRejected");
const QString DOCUMENT_SERIALIZE_POINT_MATCH_COLOR_REJECTED_STRING ("ColorRejectedString");
const QString DOCUMENT_SERIALIZE_POINT_ORDINAL ("Ordinal");
const QString DOCUMENT_SERIALIZE_POINT_POSITION_SCREEN ("PositionScreen");
const QString DOCUMENT_SERIALIZE_POINT_POSITION_GRAPH ("PositionGraph");
const QString DOCUMENT_SERIALIZE_POINTS ("Points");
const QString DOCUMENT_SERIALIZE_POINT_STYLE ("PointStyle");
const QString DOCUMENT_SERIALIZE_POINT_STYLE_COLOR ("Color");
const QString DOCUMENT_SERIALIZE_POINT_STYLE_COLOR_STRING ("ColorString");
const QString DOCUMENT_SERIALIZE_POINT_STYLE_CURVE_NAME ("CurveName");
const QString DOCUMENT_SERIALIZE_POINT_STYLE_LINE_WIDTH ("LineWidth");
const QString DOCUMENT_SERIALIZE_POINT_STYLE_RADIUS ("Radius");
const QString DOCUMENT_SERIALIZE_POINT_STYLE_SHAPE ("Shape");
const QString DOCUMENT_SERIALIZE_POINT_STYLE_SHAPE_STRING ("ShapeString");
const QString DOCUMENT_SERIALIZE_POINT_X ("X");
const QString DOCUMENT_SERIALIZE_POINT_Y ("Y");
const QString DOCUMENT_SERIALIZE_SCALE_LENGTH ("ScaleLength");
const QString DOCUMENT_SERIALIZE_SCREEN_X ("ScreenX");
const QString DOCUMENT_SERIALIZE_SCREEN_X1 ("ScreenX1");
const QString DOCUMENT_SERIALIZE_SCREEN_X_DELTA ("ScreenXDelta");
const QString DOCUMENT_SERIALIZE_SCREEN_Y ("ScreenY");
const QString DOCUMENT_SERIALIZE_SCREEN_Y1 ("ScreenY1");
const QString DOCUMENT_SERIALIZE_SCREEN_Y_DELTA ("ScreenYDelta");
const QString DOCUMENT_SERIALIZE_SEGMENTS ("Segments");
const QString DOCUMENT_SERIALIZE_SEGMENTS_FILL_CORNERS ("FillCorners");
const QString DOCUMENT_SERIALIZE_SEGMENTS_INACTIVE_OPACITY ("InactiveOpacity");
const QString DOCUMENT_SERIALIZE_SEGMENTS_LINE_COLOR ("LineColor"); 
const QString DOCUMENT_SERIALIZE_SEGMENTS_LINE_COLOR_STRING ("LineColorString");
const QString DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH ("LineWidth");
const QString DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH_ACTIVE ("LineWidthActive");
const QString DOCUMENT_SERIALIZE_SEGMENTS_LINE_WIDTH_INACTIVE ("LineWidthInactive");
const QString DOCUMENT_SERIALIZE_SEGMENTS_MIN_LENGTH ("MinLength");
const QString DOCUMENT_SERIALIZE_SEGMENTS_POINT_SEPARATION ("PointSeparation");
const QString DOCUMENT_SERIALIZE_TRANSFORM_DEFINED ("TransformDefined");
