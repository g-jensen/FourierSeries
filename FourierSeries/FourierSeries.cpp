#include <SFML/Graphics.hpp>
#include "FourierVector.h"
#include "Math.h"
#include <iostream>
#include <random>
#include <fstream>
#include <nlohmann/json.hpp>

int main()
{

    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(5, 360); // define the range

    std::mt19937 gen1(rd()); // seed the generator
    std::uniform_int_distribution<> distr1(-10, 10); // define the range

    ////////////////

    std::vector<sf::CircleShape> points;

    int graphX = 100;
    int graphY = 0;

    float vectorLengthsum = 0;

    ///////////////


    std::vector<FourierVector>* vectors = new std::vector<FourierVector>();

    std::string input;
    std::string file;
    std::ifstream myfile("config.json");
    if (myfile.is_open())
    {
        while (getline(myfile, input)) {
            file += input + "\n";
        }
        file = file.substr(0, file.size() - 1);
        myfile.close();
    }
    nlohmann::json json = nlohmann::json::parse(file);

    int n = stoi((std::string)json["n"]);

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            FourierVector first(distr1(gen1), distr1(gen1));
            first.fillColor = sf::Color::Yellow;
            first.origin = sf::Vector2f(0, 0);
            first.rotate(distr(gen));
            vectorLengthsum += first.length;
            vectors->push_back(first);
        }
        else {
            FourierVector others(distr1(gen1), distr1(gen1));
            others.fillColor = sf::Color::Green;
            others.origin = sf::Vector2f((*vectors)[i - 1].x, (*vectors)[i - 1].y);
            others.rotate(distr(gen));
            vectorLengthsum += others.length;
            vectors->push_back(others);
        }
    }

    if (n < 20) {
        graphX = vectorLengthsum + 5;
    }
    else {
        graphX = vectorLengthsum / (n / 20);
    }

    (*vectors)[vectors->size() - 1].fillColor = sf::Color::Red;

    std::vector<sf::CircleShape> line;

    bool spaceHasBeenPressed = false;

    float rotation = 0.0001;

    ///////////////

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1200, 800), "Fourier Series",sf::Style::Default,settings);

    sf::View windowView = window.getView();
    windowView.setCenter(0, 0);
    window.setView(windowView);

    window.setFramerateLimit(300);

    for (int t = 0; t < 20; t++) {
        sf::View view = window.getView();
        view.zoom(0.9);
        window.setView(view);
    }

    while (window.isOpen())
    {
        window.setFramerateLimit(300);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0.f, 0.f, (float)event.size.width, (float)event.size.height);
                window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta <= -1) {
                    sf::View view = window.getView();
                    view.zoom(1.1);
                    window.setView(view);
                }
                if (event.mouseWheelScroll.delta >= 1) {
                    sf::View view = window.getView();
                    view.zoom(0.9);
                    window.setView(view);
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    spaceHasBeenPressed = !spaceHasBeenPressed;
                }
                if (event.key.code == (sf::Keyboard::Up)) {
                    sf::View view = window.getView();
                    view.move(0, -30);
                    window.setView(view);
                }
                if (event.key.code == (sf::Keyboard::Down)) {
                    sf::View view = window.getView();
                    view.move(0, 30);
                    window.setView(view);
                }
                if (event.key.code == (sf::Keyboard::Left)) {
                    sf::View view = window.getView();
                    view.move(-30, 0);
                    window.setView(view);
                }
                if (event.key.code == (sf::Keyboard::Right)) {
                    sf::View view = window.getView();
                    view.move(30, 0);
                    window.setView(view);
                }
            }
        }

        //////////////

        if (spaceHasBeenPressed) {

            for (int i = 0; i < vectors->size(); i++) {
                if (i == 0) {
                    (*vectors)[i].rotate(rotation);
                }
                else {

                    (*vectors)[i].origin = sf::Vector2f((*vectors)[i - 1].x, (*vectors)[i - 1].y);

                    if (i % 2 == 0) {
                        (*vectors)[i].rotate(rotation);
                    }
                    else {
                        (*vectors)[i].rotate(-rotation);
                    }

                }

            }

            sf::CircleShape circle(0.1);
            circle.setPosition((*vectors)[vectors->size() - 1].x - 0.05, (*vectors)[vectors->size() - 1].y - 0.05);
            line.push_back(circle);


            for (auto& p : points) {
                p.move(1,0);
            }

            sf::CircleShape point(0.2);
            graphY = (*vectors)[vectors->size() - 1].y;
            point.setPosition(graphX,graphY);
            points.push_back(point);
        }

        window.clear(sf::Color::Black);

        for (auto& circle : line) {
            window.draw(circle);
        }

        for (auto& v : *vectors) {
            v.draw(window);
        }

        for (auto& graphPoint : points) {
            window.draw(graphPoint);
        }

        window.display();
    }

    delete vectors;

    return 0;
}