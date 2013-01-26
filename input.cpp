#include "input.h"

Input::Input() : m_xSouris(0), m_ySouris(0), m_xrel(0), m_yrel(0), m_terminer(false)
{
    // Initialisation du tableau clavier

    for(int i(0); i < SDL_NUM_SCANCODES; i++)
        m_touches[i] = false;


    // Initialisation du tableau boutonsSouris

    for(int i(0); i < 8; i++)
        m_boutonsSouris[i] = false;
}


Input::~Input()
{

}


void Input::updateEvent()
{
    // Variable SDL_Event (en statique pour rester en mémoire)

    static SDL_Event evenements;


    // Pour éviter de fausses valeurs au niveau de la souris, on réinitialise certains attributs

    m_xrel = 0;
    m_yrel = 0;

    m_boutonsSouris[SDL_BUTTON_X2] = false;
    m_boutonsSouris[SDL_BUTTON_X1] = false;


    // Mise à jour des évènements

    while(SDL_PollEvent(&evenements))
    {
        // On teste les autres évènements

        switch(evenements.type)
        {
            // Cas de pression sur une touche

            case SDL_KEYDOWN:
                m_touches[evenements.key.keysym.scancode] = true;
            break;


            // Cas du relâchement d'une touche

            case SDL_KEYUP:
                m_touches[evenements.key.keysym.scancode] = false;
            break;


            // Cas d'un mouvement de souris

            case SDL_MOUSEMOTION:

                m_xSouris = evenements.motion.x;
                m_ySouris = evenements.motion.y;

                m_xrel = evenements.motion.xrel;
                m_yrel = evenements.motion.yrel;

            break;


            // Cas de pression sur un bouton de souris

            case SDL_MOUSEBUTTONDOWN:
                m_boutonsSouris[evenements.button.button] = true;
            break;


            // Cas du relâchement d'un bouton de souris

            case SDL_MOUSEBUTTONUP:

                if(evenements.button.button != SDL_BUTTON_X2 && evenements.button.button != SDL_BUTTON_X1)
                    m_boutonsSouris[evenements.button.button] = false;

            break;


            // Cas de la fermeture de la fenêtre

            case SDL_WINDOWEVENT:

                if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
                    m_terminer = true;

            break;


            // Défaut

            default:
            break;
        }
    }
}


bool Input::terminer() const
{
    return m_terminer;
}

bool Input::getKey(int code){
	return m_touches[code];
}
