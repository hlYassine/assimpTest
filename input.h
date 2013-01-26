#ifndef DEF_INPUT
#define DEF_INPUT

#include <SDL2/SDL.h>

class Input
{
    public:

    Input();
    ~Input();

    void updateEvent();
    bool terminer() const;
    bool getKey(int code);


    private:

    bool m_touches[SDL_NUM_SCANCODES];

    int m_xSouris;
    int m_ySouris;
    int m_xrel;
    int m_yrel;

    bool m_boutonsSouris[8];
    bool m_terminer;
};

#endif
