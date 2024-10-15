#pragma once

#include "DrawDebugHelpers.h"

#define DRAW_SPHERE_COLOR(Location, Color) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 12.f, 8, Color, false, 4.f)