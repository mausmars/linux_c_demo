CREATE TABLE IF NOT EXISTS `map_level` (
    `fpid` bigint NOT NULL DEFAULT 0 COMMENT '用户id',
    `mid` text NOT NULL COMMENT '关卡id',
    `bid1` int NOT NULL DEFAULT 0 COMMENT '1建筑id',
    `state1` int NOT NULL DEFAULT 0 COMMENT '1建筑状态',
    `level1` int NOT NULL DEFAULT 0 COMMENT '1建筑等级',
    `bid2` int NOT NULL DEFAULT 0 COMMENT '2建筑id',
    `state2` int NOT NULL DEFAULT 0 COMMENT '2建筑状态',
    `level2` int NOT NULL DEFAULT 0 COMMENT '2建筑等级',
    `bid3` int NOT NULL DEFAULT 0 COMMENT '3建筑id',
    `state3` int NOT NULL DEFAULT 0 COMMENT '3建筑状态',
    `level3` int NOT NULL DEFAULT 0 COMMENT '3建筑等级',
    `bid4` int NOT NULL DEFAULT 0 COMMENT '4建筑id',
    `state4` int NOT NULL DEFAULT 0 COMMENT '4建筑状态',
    `level4` int NOT NULL DEFAULT 0 COMMENT '4建筑等级',
    PRIMARY KEY (`fpid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;