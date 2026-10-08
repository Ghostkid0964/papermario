#include "common.h"

/* =========================================================
 * BOOT CONFIGURATION
 * =========================================================
 *
 * Change BOOT_STAGE to test different initialization levels.
 *
 * 2 = Game status
 * 3 = Input
 * 4 = Render/tasks/scripts
 * 5 = Player status
 */

#define BOOT_STAGE 3


/* =========================================================
 * FORWARD DECLARATIONS
 * ========================================================= */

void boot3ds_progress(s32 step);


/* =========================================================
 * GAME STATUS
 * ========================================================= */

static void boot_init_game_status(void)
{
    gOverrideFlags = 0;
    gGameStatusPtr = &gGameStatus;

    boot3ds_progress(2);
}


/* =========================================================
 * INPUT SYSTEM
 * ========================================================= */

static void boot_init_input(void)
{
    clear_input();

    boot3ds_progress(3);
}


/* =========================================================
 * RENDER / TASK SYSTEM
 * ========================================================= */

static void boot_init_render_tasks(void)
{
    clear_render_tasks();

    boot3ds_progress(41);
}


/* =========================================================
 * WORKER SYSTEM
 * ========================================================= */

static void boot_init_workers(void)
{
    clear_worker_list();

    boot3ds_progress(42);
}


/* =========================================================
 * SCRIPT SYSTEM
 * ========================================================= */

static void boot_init_scripts(void)
{
    clear_script_list();

    boot3ds_progress(43);
}


/* =========================================================
 * PLAYER STATUS
 * ========================================================= */

static void boot_init_player_status(void)
{
    clear_player_status();

    boot3ds_progress(5);
}


/* =========================================================
 * MAIN BOOT INITIALIZATION
 * ========================================================= */

void boot3ds_init(void)
{
    /* -----------------------------------------------------
     * Stage 2: Game status
     * ----------------------------------------------------- */

    boot_init_game_status();


    /* -----------------------------------------------------
     * Stage 3: Input
     * ----------------------------------------------------- */

#if BOOT_STAGE >= 3
    boot_init_input();
#endif


    /* -----------------------------------------------------
     * Stage 4: Render / workers / scripts
     * ----------------------------------------------------- */

#if BOOT_STAGE >= 4
    boot_init_render_tasks();
    boot_init_workers();
    boot_init_scripts();
#endif


    /* -----------------------------------------------------
     * Stage 5: Player status
     * ----------------------------------------------------- */

#if BOOT_STAGE >= 5
    boot_init_player_status();
#endif
}
