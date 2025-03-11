#ifndef MENU_H
#define MENU_H

#include "../common/defs.h"
#include "../kinematics/body.h"

void draw_menu(Body* target);
void draw_text_field(const char* label, const char* value, int* currentY);

#endif // MENU_H