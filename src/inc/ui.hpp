#ifndef TEABAG_UI_HPP
#define TEABAG_UI_HPP

#include "defines.hpp"
#include "reader.hpp"
#include "error.hpp"
#include "fontmanager.hpp"

#include <string>

TEABAG_NS

class World;

class TEABAG_API UI {
private:
    friend class World;

    void queue(std::string name);
    void load();

    std::string queued;
   
    internal::FontManager fonts; 
};

TEABAG_NS_END

#endif
