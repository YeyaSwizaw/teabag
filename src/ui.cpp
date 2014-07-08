#include "inc/ui.hpp"

TEABAG_NS

void UI::queue(std::string name) {
   queued = name;
} 

void UI::load() {
    if(!queued.empty()) {
        std::string file = TEABAG_UI_TEA(queued);

        internal::Reader reader(file);
        if(!reader) {
            throw FileOpenError(file);
        } 

        while(reader.nextLine()) {
            std::string option;
            if(!reader.get(option)) {
                throw LineReadError(file, reader.line);
            } 

            if(option == "font") {
                std::string name, font;
                int size;

                if(!reader.get(name, font, size)) {
                    throw LineReadError(file, reader.line);
                } 

                fonts.queueFont(name, font, size);
            } 
        } 

        queued.clear();

        fonts.loadQueue();
    } 
} 


TEABAG_NS_END
