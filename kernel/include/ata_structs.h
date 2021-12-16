#ifndef __ATA_STRUCTS_H_
#define __ATA_STRUCTS_H_

#include "stdint.h"

typedef struct tagIDENTIFY_DEVICE_DATA {
    uint8_t		general_config[2];
    uint8_t		serial[21];
    uint8_t		firmware[9];
    uint8_t		model[41];
    uint8_t		world_wide[9];

    uint8_t		sec_level:1;
    uint8_t		sec_enh_erase_sup:1;
    uint8_t		sec_count_exp:1;
    uint8_t		sec_frozen:1;
    uint8_t		sec_locked:1;
    uint8_t		sec_enabled:1;
    uint8_t		sec_supported:1;

    uint16_t	sec_erase_time;
    uint16_t	sec_enh_erase_time;

    uint8_t		cmd_feat_supported_83[2];

    uint64_t	max_lba;
} IDENTIFY_DEVICE_DATA;

typedef struct tagSMART_DATA {
    uint8_t self_test_status;
    uint8_t smart_capability[2];
    uint16_t self_test_short_poll;
    uint16_t self_test_ext_poll;
} SMART_DATA;

#endif //__ATA_STRUCTS_H_