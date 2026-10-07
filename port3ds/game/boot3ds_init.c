#include "common.h"
#include "functions.h"
#include "game_modes.h"

extern s8 gGameStepDelayCount;
extern void boot3ds_progress(int step);

void boot3ds_init(void) {
    s32 i;

    gOverrideFlags = 0;
    gGameStatusPtr->unk_79 = 0;
    gGameStatusPtr->backgroundFlags = 0;
    gGameStatusPtr->musicEnabled = true;
    gGameStatusPtr->healthBarsEnabled = true;
    gGameStatusPtr->introPart = INTRO_PART_NONE;
    gGameStatusPtr->demoBattleFlags = 0;
    gGameStatusPtr->multiplayerEnabled = false;
    gGameStatusPtr->altViewportOffset.x = -8;
    gGameStatusPtr->altViewportOffset.y = 4;
    gTimeFreezeMode = TIME_FREEZE_NONE;
    gGameStatusPtr->debugQuizmo = 0;
    gGameStatusPtr->unk_13C = 0;
    gGameStepDelayCount = 5;
    gGameStatusPtr->saveCount = 0;

    boot3ds_progress(1);

    clear_input();
    boot3ds_progress(2);

    general_heap_create();
    boot3ds_progress(3);

    clear_render_tasks();
    boot3ds_progress(4);

    clear_worker_list();
    boot3ds_progress(5);

    clear_script_list();
    boot3ds_progress(6);

    create_cameras();
    boot3ds_progress(7);

    clear_player_status();
    boot3ds_progress(8);

    spr_init_sprites(PLAYER_SPRITES_MARIO_WORLD);
    boot3ds_progress(9);

    clear_entity_models();
    boot3ds_progress(10);

    clear_animator_list();
    boot3ds_progress(11);

    clear_model_data();
    boot3ds_progress(12);

    clear_sprite_shading_data();
    boot3ds_progress(13);

    reset_background_settings();
    boot3ds_progress(14);

    clear_character_set();
    boot3ds_progress(15);

    clear_printers();
    boot3ds_progress(16);

    clear_game_mode();
    boot3ds_progress(17);

    clear_npcs();
    boot3ds_progress(18);

    hud_element_clear_cache();
    boot3ds_progress(19);

    clear_trigger_data();
    boot3ds_progress(20);

    clear_entity_data(false);
    boot3ds_progress(21);

    clear_player_data();
    boot3ds_progress(22);

    init_encounter_status();
    boot3ds_progress(23);

    clear_screen_overlays();
    boot3ds_progress(24);

    clear_effect_data();
    boot3ds_progress(25);

    clear_saved_variables();
    boot3ds_progress(26);

    clear_item_entity_data();
    boot3ds_progress(27);

    bgm_reset_sequence_players();
    boot3ds_progress(28);

    reset_ambient_sounds();
    boot3ds_progress(29);

    sfx_clear_sounds();
    boot3ds_progress(30);

    clear_windows();
    boot3ds_progress(31);

    initialize_curtains();
    boot3ds_progress(32);

    poll_rumble();
    boot3ds_progress(33);

    for (i = 0; i < ARRAY_COUNT(gGameStatusPtr->holdRepeatInterval); i++) {
        gGameStatusPtr->holdRepeatInterval[i] = 3;
        gGameStatusPtr->holdDelayTime[i] = 12;
    }

    boot3ds_progress(34);

    gOverrideFlags |= GLOBAL_OVERRIDES_DISABLE_DRAW_FRAME;
    set_game_mode(GAME_MODE_STARTUP);
    boot3ds_progress(35);
}
