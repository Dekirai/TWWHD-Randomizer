
#pragma once

#include <string>

enum struct Area : uint32_t
{
    INVALID = 0,
    Root,
    LinksSpawn,
    MailboxChecks,
    TheGreatSea,
    ForsakenFortress,
    ForsakenFortressInnerCourtyard,
    ForsakenFortressBarrelStorageRoomLower,
    ForsakenFortressNorthHallwayLower,
    ForsakenFortressMessHallLower,
    ForsakenFortressEastHallwayLower,
    ForsakenFortressJailCellLower,
    ForsakenFortressNorthwestHallwayLower,
    ForsakenFortressBoatRoomLower,
    ForsakenFortressSouthwestHallwayLower,
    ForsakenFortressSleepingQuarters,
    ForsakenFortressSleepingQuartersOutsideLedge,
    ForsakenFortressSouthHallwayUpper,
    ForsakenFortressUpSwitchBackStairs,
    ForsakenFortressJailCellUpper,
    ForsakenFortressMessHallUpperEast,
    ForsakenFortressMessHallUpperWest,
    ForsakenFortressNorthHallwayUpper,
    ForsakenFortressBarrelStorageRoomUpperEast,
    ForsakenFortressBarrelStorageRoomUpperWest,
    ForsakenFortressNorthwestHallwayUpper,
    ForsakenFortressBoatRoomUpper,
    ForsakenFortressSouthwestHallwayUpper,
    ForsakenFortressSleepingQuartersPastHammerPegs,
    ForsakenFortressOutsidePathToBoss,
    ForsakenFortressOutsidePathToBossPastSidleGaps,
    ForsakenFortressBossRoom,
    StarIsland,
    StarIslandCave,
    StarIslandLookoutPlatform,
    NorthernFairyIsland,
    NorthernFairyIslandGreatFairyFountain,
    NorthernFairyIslandSubmarineExterior,
    NorthernFairyIslandSubmarineInterior,
    GaleIsle,
    GaleIsleInterior,
    CrescentMoonIsland,
    CrescentMoonSubmarineExterior,
    CrescentMoonSubmarineInterior,
    SevenStarIsles,
    SevenStarLookoutPlatforms,
    OverlookIsland,
    OverlookIslandUpperIsles,
    OverlookCave,
    FourEyeReef,
    MotherAndChildIsles,
    MotherAndChildInsideMotherIsle,
    SpectacleIsland,
    SpectacleBeedleShop,
    WindfallIsland,
    WindfallJail,
    WindfallSchoolOfJoy,
    WindfallLenzosHouseFromBottomEntry,
    WindfallLenzosHouseLower,
    WindfallLenzosHouseUpper,
    WindfallLenzosUpperLedge,
    WindfallCafeBar,
    WindfallBattleSquidInterior,
    WindfallBattleSquidUpperLedge,
    WindfallHouseOfWealthLower,
    WindfallHouseOfWealthUpper,
    WindfallPotionShop,
    WindfallBombShop,
    WindfallBombShopUpperLedge,
    WindfallPirateShip,
    WindfallBeedleShop,
    PawprintIsle,
    PawprintChuChuCave,
    PawprintWizzrobeCaveIsle,
    PawprintWizzrobeCave,
    PawprintLookoutPlatform,
    PawprintBeedleShop,
    DragonRoostIsland,
    DragonRoostRitoAerie,
    DragonRoostPond,
    DragonRoostPondPastStatues,
    DragonRoostPondUpperLedge,
    DragonRoostIslandFlightDeck,
    DragonRoostKomalisRoom,
    DragonRoostIslandCave,
    DragonRoostBeedleShop,
    FlightControlPlatform,
    FlightControlSubmarineExterior,
    FlightControlSubmarineInterior,
    WesternFairyIsland,
    WesternFairyIslandPastFlames,
    WesternFairyGreatFairyFountain,
    WesternFairyLookoutPlatform,
    RockSpireIsle,
    RockSpireUpperLedges,
    RockSpireBeedleShop,
    RockSpirePlatforms,
    RockSpireCave,
    TingleIsland,
    NorthernTriangleIsland,
    EasternFairyIsland,
    EasternFairyIslandPastBoulder,
    EasternFairyGreatFairyFountain,
    EasternFairyLookoutPlatform,
    FireMountain,
    FireMountainInterior,
    FireMountainLookoutPlatform,
    StarBeltArchipelago,
    StarBeltLookoutPlatform,
    ThreeEyeReef,
    GreatfishIsle,
    GreatfishBeedleShop,
    CyclopsReef,
    CyclopsReefLookoutPlatform,
    SixEyeReef,
    SixEyeReefSubmarineExterior,
    SixEyeReefSubmarineInterior,
    SixEyeReefLookoutPlatform,
    TowerOfTheGods,
    TowerOfTheGodsBeedleShop,
    EasternTriangleIsland,
    EasternTriangleBeedleShop,
    ThornedFairyIsland,
    ThornedFairyIslandPastTentacles,
    ThornedFairyGreatFairyFountain,
    ThornedFairyLookoutPlatforms,
    NeedleRockIsle,
    NeedleRockCave,
    IsletOfSteel,
    IsletOfSteelInterior,
    IsletOfSteelLookoutPlatform,
    StoneWatcherIsland,
    StoneWatcherCave,
    StoneWatcherLookoutPlatform,
    SouthernTriangleIsland,
    SouthernTriangleBeedleShop,
    PrivateOasis,
    TheCabana,
    CabanaLabyrinth,
    BombIsland,
    BombIslandCave,
    BombIslandSubmarineExterior,
    BombIslandSubmarineInterior,
    BombIslandLookoutPlatform,
    BirdsPeakRock,
    BirdsPeakRockBehindBars,
    BirdsPeakRockCave,
    DiamondSteppeIsland,
    DiamondSteppeUpperIsland,
    DiamondSteppeWarpMaze,
    FiveEyeReef,
    FiveEyeReefLookoutPlatform,
    SharkIsland,
    SharkIslandCave,
    SharkIslandBeedleShop,
    SouthernFairyIsland,
    SouthernFairyIslandBehindWoodenBarrier,
    SouthernFairyGreatFairyFountain,
    SouthernFairyLookoutPlatforms,
    IceRingIsle,
    IceRingInterior,
    IceRingInnerCave,
    ForestHaven,
    ForestHavenInterior,
    ForestPotionShop,
    ForestHavenInteriorUpperBabaBuds,
    ForestHavenInteriorNorthLedge,
    ForestHavenInteriorWestLowerLedge,
    ForestHavenInteriorWestUpperLedge,
    ForestHavenInteriorSouthLedge,
    ForestHavenExteriorNorthLedge,
    ForestHavenExteriorWestLowerLedge,
    ForestHavenExteriorWestUpperLedge,
    ForestHavenExteriorSouthLedge,
    ForestHavenSouthIsle,
    ForestHavenNintendoGalleryIsle,
    ForestHavenNintendoGallery,
    ForestHavenWaterfallCave,
    FWEntrancePlatform,
    ForestHavenBeedleShop,
    CliffPlateauIsles,
    CliffPlateauCave,
    CliffPlateauCavePastWoodenBarrier,
    CliffPlateauHighestIsle,
    CliffPlateauLookoutPlatform,
    HorseshoeIsle,
    HorseshoeIslePastTentacles,
    HorseshoeCave,
    HorseshoeLookoutPlatforms,
    OutsetIsland,
    OutsetNearBridge,
    OutsetAcrossBridge,
    OutsetNearSavageHeadstone,
    OutsetLinksHouse,
    OutsetUnderLinksHouse,
    OutsetOrcasHouse,
    OutsetSturgeonsHouse,
    OutsetRosesHouse,
    OutsetRosesAttic,
    OutsetMesasHouse,
    OutsetForestOfFairies,
    OutsetGreatFairyFountain,
    OutsetSavageLabyrinth,
    OutsetSavageFloor30,
    OutsetSavageFloor50,
    OutsetJabunsCave,
    OutsetBeedleShop,
    HeadstoneIsland,
    HeadstoneIslandInterior,
    HeadstoneIslandSubmarineExterior,
    HeadstoneIslandSubmarineInterior,
    TwoEyeReef,
    TwoEyeReefLookoutPlatform,
    AngularIsles,
    AngularIslesSmallIsle,
    AngularIslesCave,
    BoatingCourse,
    BoatingCourseSmallIsle,
    BoatingCourseCave,
    FiveStarIsles,
    FiveStarSubmarineExterior,
    FiveStarSubmarineInterior,
    FiveStarLookoutPlatform,
    GhostShipInterior,
    DRCFirstRoom,
    DRCHubRoomLowerArea,
    DRCHubRoomLowerAreaNearDimRoom,
    DRCMapChestRoom,
    DRCLowerDimRoomBokoblinArea,
    DRCLowerDimRoomChuchuArea,
    DRCSwitchBehindWoodenBarrierRoom,
    DRCOutsideLowerArea,
    DRCRatRoom,
    DRCOutsideUpperArea,
    DRCDarkRoomChestArea,
    DRCDarkRoomPastWoodenBarrier,
    DRCHubRoomUpperBridge,
    DRCTripleBokoblinRoom,
    DRCMagtailLavaGeyserRoom,
    DRCBossDoorRoomBeforeLava,
    DRCBossDoorRoomAcrossLava,
    DRCMiniBossUpperArea,
    DRCMiniBossLowerArea,
    DRCRopeBridgeUnderpassRoom,
    DRCHubRoomHighestPlatform,
    DRCHubRoomMouthArea,
    DRCBeforeBigKeyRoomUpper,
    DRCBeforeBigKeyRoomLower,
    DRCBigKeyRoom,
    DRCBossRoom,
    FWFirstRoom,
    FWSecondRoomSouthPlatform,
    FWSecondRoomNorthPlatform,
    FWSecondRoomGroundPath,
    FWShortCableRideRoomSouthSide,
    FWShortCableRideRoomNorthSide,
    FWHoleInTreeRoomNearLowerDoor,
    FWHoleInTreeRoomNearUpperDoor,
    FWVineCircleHallway,
    FWHubRoomMiddleArea,
    FWHubRoomUpperArea,
    FWMorthPitHallway,
    FWVineMazeRoom,
    FWCableRideAbovePoisonWaterRoomLowerWest,
    FWCableRideAbovePoisonWaterRoomLowerEast,
    FWTallRoomBeforeMiniBoss,
    FWMiniBossRoom,
    FWCableRideAbovePoisonWaterRoomUpperEast,
    FWCableRideAbovePoisonWaterRoomUpperWest,
    FWHubRoomHighestPlatform,
    FWHubRoomLowerArea,
    FWForkedHallwayLower,
    FWPoisonRiverRoomBeforeRiver,
    FWPoisonRiverRoomAfterRiver,
    FWTingleChestRoom,
    FWBigKeyRoom,
    FWBigKeyRoomHigherLedge,
    FWForkedHallwayHigherLedge,
    FWMothulaHallway,
    FWBossDoorRoom,
    FWBossRoom,
    TOTGEntranceRoom,
    TOTGEastGoldenStatueRoom,
    TOTGEntranceRoomPastGate,
    TOTGHopAcrossFloatingBoxesRoom,
    TOTGMapChestRoom,
    TOTGEntranceRoomPastBombableWalls,
    TOTGSkullsRoom,
    TOTGWestGoldenStatueRoom,
    TOTGEntranceRoomPastWaterfall,
    TOTGRisingPlatformsRoom,
    TOTGHubRoom,
    TOTGFirstStatueCorridor,
    TOTGFirstStatueRoom,
    TOTGFirstStatueCorridorArmosKnightsRoom,
    TOTGSecondStatueCorridorNearHubRoom,
    TOTGSecondStatueCorridorNearSecondStatueRoom,
    TOTGSecondStatueRoomNearCorridor,
    TOTGSecondStatueRoomNearStatue,
    TOTGSecondStatueCorridorNearMiniBossRoom,
    TOTGMiniBossRoom,
    TOTGThirdStatueCorridor,
    TOTGManyMovingPlatformsRoom,
    TOTGThirdStatueCorridorPastBombableWall,
    TOTGThirdStatueCorridorArmosKnightsRoom,
    TOTGThirdStatueRoom,
    TOTGThirdStatueRoomPastLasers,
    TOTGBigKeyRoom,
    TOTGOutsideArea,
    TOTGBossRoom,
    ETFirstRoom,
    ETEarlyTwoSwitchesRoom,
    ETMapChestRoom,
    ETGiantStatueRoom,
    ETFirstCrypt,
    ETSmallRoomSouthOfFirstCrypt,
    ETChuChusAndSwitchesRoom,
    ETBlockPushCorridor,
    ETTwoMoblinsAndPoesRoom,
    ETTwoMoblinsAndPoesRoomPastStairs,
    ETSecondCrypt,
    ETMiniBossRoom,
    ETMiniBossRoomUpperLedge,
    ETTwoMoblinsAndPoesRoomPastLightWall,
    ETGiantStatueRoomUpperLedge,
    ETGiantStatueRoomUnderStatue,
    ETHangingBridgeRoom,
    ETBasementHubRoom,
    ETFoggyFloormastersRoom,
    ETPoesAndBubblesRoomBehindGrating,
    ETBasementHubRoomUpperLedge,
    ETPoesAndBubblesRoom,
    ETThirdCrypt,
    ETBossDoorRoom,
    ETManyMirrorsRoom,
    ETManyMirrorsRoomPastLightWall,
    ETBigKeyChestRoom,
    ETTripleStalfosRoom,
    ETBossRoom,
    WTFirstRoom,
    WTFirstWarpPotRoomFront,
    WTFirstWarpPotRoomBack,
    WTEarlyTurnFloorRoom,
    WTEarlyTurnFloorRoomPastTurnFloor,
    WTMakarCaptureRoom,
    WTHubRoomMiddleWestPlatform,
    WTHubRoomMiddleNorthPlatform,
    WTHubRoomMiddleEastPlatform,
    WTSongStoneAndTurnPlatformRoomNearHubRoom,
    WTSongStoneAndTurnPlatformRoomNearCyclonesRoom,
    WTBigKeyChestRoom,
    WTManyCyclonesRoomEastSide,
    WTManyCyclonesRoomWestSide,
    WTHubRoomMiddleSouthPlatform,
    WTHubRoomCompassChestPlatform,
    WTHubRoomLowerArea,
    WTMiniBossRoom,
    WTCrackedFloorsRoom,
    WTMakarCaptureRoomUpperPlatform,
    WTBlueBubblesRoom,
    WTBlueBubblesRoomUpperLedge,
    WTHubRoomUpperNorthPlatform,
    WTHubRoomUpperEastPlatform,
    WTHubRoomUpperSouthPlatform,
    WTSevenArmosRoom,
    WTHubRoomBelowFan,
    WTTallBasementRoom,
    WTLongNarrowRoom,
    WTLongNarrowRoomPastGap,
    WTThreeBigFansRoom,
    WTThreeBigFansRoomPastSongStone,
    WTBossRoom,
    HyruleCastleFront,
    HyruleCastleInterior,
    HyruleCastleSwordChamber,
    HyruleCastleBridge,
    HyruleFieldPath,
    HyruleFieldPathPastBrokenBridge,
    GanonsTowerTrialsHub,
    GanonsTowerDRCTrial,
    GanonsTowerGohmaRefight,
    GanonsTowerFWTrial,
    GanonsTowerKalleDemosRefight,
    GanonsTowerETTrial,
    GanonsTowerJalhallaRefight,
    GanonsTowerWTTrial,
    GanonsTowerMolgeraRefight,
    GanonsTowerFirstStaircase,
    GanonsTowerMiddleHubRoom,
    GanonsTowerPhantomGanonMaze,
    GanonsTowerFinalStaircase,
    GanonsTowerPuppetGanonBossRoom,
    GanonsTowerSpire,
    COUNT
};

#define AREA_COUNT static_cast<std::underlying_type_t<Area>>(Area::COUNT)

Area nameToArea(const std::string& name);
std::string areaToName(const Area& area);
void storeNewAreaPrettyName(const Area& area, std::string prettyName);
std::string areaToPrettyName(const Area& area);
uint32_t areaAsIndex(Area area);
Area indexAsArea(uint32_t index);
Area roomIndexToIslandArea(const uint8_t& startingIslandRoomIndex);
