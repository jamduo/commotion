#include "raylib.h"

#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "common/defs.h"
#include "integrators/euler.h"
#include "kinematics/forces.h"
#include "kinematics/bodies.h"
#include "ui/menu.h"
#include "demo/demo.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);          // Update and draw one frame

typedef struct {
	Body* target;
	bool isDragging;
	Vec2 targetPosition;
} DragState;
#define DRAGSTATE_NONE ((DragState){.target = NULL, .isDragging = false, .targetPosition = vec2(0, 0)})

typedef struct {
    real t;
    real dt;
    real accumulator;
    real lastTime;
    DragState dragState;
    bool paused;
    Body* target;
    Camera2D camera;
} SimulationState;

static SimulationState state;

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "commotion");

	state = (SimulationState){
        .t = 0.0f,
        .dt = 0.01f,
        .accumulator = 0.0f,
        .lastTime = GetTime(),
        .dragState = DRAGSTATE_NONE,
        .paused = false,
        .target = NULL,
        // .camera, initialized below
    };
	
	demo_init(&state.camera);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void)
{

    // Update
    //----------------------------------------------------------------------------------
    float currentTime = GetTime();
    float frameTime = currentTime - state.lastTime;
    state.lastTime = currentTime;

    if (!state.paused) {
        state.accumulator += frameTime * 10.0f;
    }

    // TODO: This should a function
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        Vector2 world = GetScreenToWorld2D(mouse, state.camera);
        
        Vec2 position = vec2(world.x, world.y);
        Body* found_body = bodies_nearest(position);

        if (!state.paused) {
            state.target = found_body;
        }

        if (found_body && state.paused) {
            state.dragState.target = found_body;
            state.dragState.isDragging = true;
            state.dragState.targetPosition = found_body->state.position;
        } else {
            state.dragState = DRAGSTATE_NONE;
        }
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        if (state.dragState.isDragging && state.dragState.target) {
            state.dragState.target->state.position = state.dragState.targetPosition;
            state.dragState = DRAGSTATE_NONE;
        }
    }

    if (state.dragState.isDragging && state.dragState.target) {
        // Get the world space position of the mouse
        Vector2 mouse = GetMousePosition();
        Vector2 world = GetScreenToWorld2D(mouse, state.camera);
        state.dragState.targetPosition = vec2(world.x, world.y);
    }

    // Reset scene :)
    if (IsKeyPressed(KEY_R)) {
        bodies_clear();
        state.accumulator = 0;
        demo_init(&state.camera);
    }

    if (IsKeyPressed(KEY_SPACE)) {
        state.paused = !state.paused;
    }

    while (state.accumulator >= state.dt && !state.paused) {
        state.t += state.dt;
        state.accumulator -= state.dt;

        demo_update(state.dt);
        // TODO: move this to a bodies_* function
        for (size_t i = 0; i < num_bodies; i++) {
            body_integrate(&bodies[i], state.dt);
        }
    }
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    
    ClearBackground(BLACK);
    if (state.paused) {
        state.target = NULL;
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(MAGENTA, 0.1f));
    }
    
    BeginMode2D(state.camera);
    if (state.target) {
        state.camera.target = (Vector2){
            .x = state.target->state.position.x,
            .y = state.target->state.position.y,
        };
    }
    for (size_t i = 0; i < num_bodies; i++) {
        body_draw(&bodies[i], state.target);
    }
    
    if (state.dragState.isDragging && state.dragState.target && state.paused) {
        Body ghost = *state.dragState.target;
        ghost.color = Fade(ghost.color, 0.5f);
        ghost.state.position = state.dragState.targetPosition;
        body_draw(&ghost, state.target);
    }
    EndMode2D();

    draw_menu(state.target);
    
    DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}
