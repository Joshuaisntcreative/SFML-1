#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string>

int windowLength = 1280;
int windowWidth = 720;



void bubbleSort(std::vector<sf::RectangleShape>& rectangles) {
    for (size_t i = 0; i < rectangles.size(); i++) {
        for (size_t j = 0; j < rectangles.size() - 1; j++) {
            const float height0 = rectangles[j].getSize().y;
            const float height1 = rectangles[j + 1].getSize().y;

            if (height0 > height1) {
                std::swap(rectangles[j], rectangles[j + 1]);
            }
        }
    }
}

void repositionRectangles(std::vector<sf::RectangleShape>& rectangles, int windowWidth) {
    int currxPos = 0;
    for (auto& rectangle : rectangles) {
        float height = rectangle.getSize().y;
        rectangle.setPosition(currxPos, windowWidth - height);
        currxPos += 10;
    }
}


void clockwork(sf::Clock &clock, sf::Text &text) {
    sf::Time t = clock.getElapsedTime();
    float f = t.asSeconds();
    std::string s = std::to_string(f);
    text.setString("Timer: " + s);
}

//method is only changing the color of the first rectangle
void coloredRectangles(sf::Clock& clock, std::vector<sf::RectangleShape>& rectangles, sf::Time delay) {
    for (auto& rectangle : rectangles) {
        if (clock.getElapsedTime() >= delay) {
            rectangle.setFillColor(sf::Color::Green);
            clock.restart();
        }
    }
}


int main() {

    sf::RenderWindow window(sf::VideoMode(windowLength, windowWidth), "SFML works!");
    window.setFramerateLimit(60);
    int currxPos = 0;
    sf::Font font;
    sf::Time delay = sf::seconds(2.0f);
    if (!font.loadFromFile(".\\Dependencies\\ROCK.TTF")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    sf::Clock clock;


    sf::Text text("Press 'S' to sort", font, 20);
    text.setPosition(10, 10);
    sf::Text time("Timer:", font, 20);
    time.setPosition(10, 30);


    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<sf::RectangleShape> rectangles;


    for (int i = 0; i < 128; i++) {
        float height = rand() % 520 + 70;
        sf::RectangleShape rectangle(sf::Vector2f(9, height));
        rectangle.setPosition(currxPos, windowWidth - height);
        rectangle.setOutlineColor(sf::Color::Black);
        rectangle.setOutlineThickness(1.0f);

        currxPos += 10;
        rectangles.push_back(rectangle);
    }


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                bubbleSort(rectangles);
                repositionRectangles(rectangles, windowWidth);
                text.setString("Sort complete");
            }
        }

        coloredRectangles(clock, rectangles, delay);
        clockwork(clock, time);



        window.clear();

        for (const auto& rectangle : rectangles) {
              window.draw(rectangle);
        }

        window.draw(text);
        window.draw(time);
        window.display();
    }
        return 0;
        
 }
    