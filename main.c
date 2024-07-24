#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PADDLE_WIDTH = 100.0f;
const float PADDLE_HEIGHT = 20.0f;
const float BALL_RADIUS = 10.0f;
const float PADDLE_SPEED = 500.0f;
sf::Vector2f BALL_SPEED = { 300.0f, 300.0f };

class Paddle {
public:
    Paddle(float startX, float startY) {
        shape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
        shape.setPosition(startX, startY);
        shape.setFillColor(sf::Color::White);
        speed = PADDLE_SPEED;
    }

    void update(float deltaTime) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) shape.move(-speed * deltaTime, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) shape.move(speed * deltaTime, 0);
    }

    void draw(sf::RenderWindow& window) { window.draw(shape); }

    sf::FloatRect getGlobalBounds() const { return shape.getGlobalBounds(); }

private:
    sf::RectangleShape shape;
    float speed;
};

class Ball {
public:
    Ball(float startX, float startY) {
        shape.setRadius(BALL_RADIUS);
        shape.setPosition(startX, startY);
        shape.setFillColor(sf::Color::White);
        velocity = BALL_SPEED;
    }

    void update(float deltaTime) {
        shape.move(velocity * deltaTime);

        if (shape.getPosition().x - BALL_RADIUS < 0 || shape.getPosition().x + BALL_RADIUS > WINDOW_WIDTH)
            velocity.x = -velocity.x;

        if (shape.getPosition().y - BALL_RADIUS < 0 || shape.getPosition().y + BALL_RADIUS > WINDOW_HEIGHT)
            velocity.y = -velocity.y;
    }

    void draw(sf::RenderWindow& window) { window.draw(shape); }

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ping Pong");

    Paddle paddle1(WINDOW_WIDTH / 2.0f - PADDLE_WIDTH / 2.0f, WINDOW_HEIGHT - PADDLE_HEIGHT - 10.0f);
    Paddle paddle2(WINDOW_WIDTH / 2.0f - PADDLE_WIDTH / 2.0f, 10.0f);
    Ball ball(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        paddle1.update(0.016f);
        ball.update(0.016f);

        window.clear(sf::Color::Black);
        paddle1.draw(window);
        paddle2.draw(window);
        ball.draw(window);
        window.display();
    }

    return 0;
}
