#include <SDL3/SDL.h>

namespace TCS {
    struct Component {};

    struct Modes : public Component {
        int alpha;
        SDL_BlendMode b_mode;
        SDL_FlipMode f_mode;
        SDL_ScaleMode s_mode;
    };

    struct Color : public Component {
        int r;
        int g;
        int b;
    };

    

} // namespace TCS