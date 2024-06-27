#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    // Create a window
    RenderWindow window(VideoMode(800, 600), "SFML Example");

    // Create a circle
    CircleShape circle(50);
    circle.setFillColor(Color::Green);
    circle.setPosition(375, 275);

    // Set the speed of the circle
    float speed = 1.0f;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // Move the circle based on arrow key input
        if (Keyboard::isKeyPressed(Keyboard::Left))
            circle.move(-speed, 0);
        if (Keyboard::isKeyPressed(Keyboard::Right))
            circle.move(speed, 0);
        if (Keyboard::isKeyPressed(Keyboard::Up))
            circle.move(0, -speed);
        if (Keyboard::isKeyPressed(Keyboard::Down))
            circle.move(0, speed);

        // Clear the window
        window.clear();

        // Draw the circle
        window.draw(circle);

        // Display the content of the window
        window.display();
    }

    return 0;
}
