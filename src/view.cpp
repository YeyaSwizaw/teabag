#include "inc/view.hpp"

TEABAG_NS

void View::resize(int w, int h)  {
    sf::View view = window.getView();
    view.setSize(w, h);
    window.setView(view);
} 

void View::scroll(int x, int y) {
    sf::View view = window.getView();
    view.move(x, y);
    window.setView(view);
} 

void View::centerOn(int x, int y) {
    sf::View view = window.getView();
    view.setCenter(x, y);
    window.setView(view);
} 

int View::x() const {
    return window.getView().getCenter().x;
} 

int View::y() const {
    return window.getView().getCenter().y;
} 

int View::w() const {
    return window.getView().getSize().x;
} 

int View::h() const {
    return window.getView().getSize().y;
} 

TEABAG_NS_END
