#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace sf;
using namespace std;

//clock of animations 
Clock qab;
Clock eab;
Clock rab;
Clock wab;

// Main character status structure
struct status {
    Sprite wizard;
    Texture wiz_tx;
    int max_hp = 1000;
    float hp = max_hp;
    int max_mana = 400;
    float mana = max_mana;
    float movementspeed = 200.f;
    float abilitypower = 0;
    float armor = 0;
    float abilityhaste = 0;
    float lifesteal = 0;
    float armor_pen;
    float dash = 50.f;
    float autodamage = 10;
    float auto_cooldown_duration = 0.5f;
    //float firstabilitydamage = 250;
    //float cooldown_ability = 18;
    float time_warp_cooldown = 50.0f;  // Cooldown duration (in seconds)
    float time_warp_duration = 15.0f;  // Effect duration (in seconds)
    float time_warp_slowdown_factor = 0.05f;  // Slowdown factor (e.g., 0.5 = half speed)
    bool time_warp_active = false;  // Whether the ability is active
    Clock time_warp_timer;  // Timer to manage ability duration and cooldown
    float flash_distance = 200.0f; // Distance for the flash ability (in pixels)
    float flash_cooldown = 8.0f; // Cooldown duration for the flash ability (in seconds)
    Clock flash_timer; // Timer to manage flash ability cooldown
    float fire_damage = 20.0f; // Damage per second to the enemy
    float fire_duration = 5.0f; // Duration of the fire (in seconds)
    float fire_cooldown = 10.0f; // Cooldown duration for the fire ability (in seconds)
    Clock fire_timer; // Timer to manage the ability duration and cooldown
    bool fire_active = false; // Whether the fire ability is active

} wizard;

//animation
struct ani
{
    int i = 0, u;
    float timer = 0;
    float delay = .2; float delayq = .1, delaym = .1;
    bool aq = false, ae = false, ar = false, aw = false, lr = true, motion_right = false;

}animation;

void idle(ani& animation, float dt, status& wizard);
void ab(ani& animation, float dt, status& wizard);
void abe(ani& animation, float dt, status& wizard);
void abw(ani& animation, float dt, status& wizard);

void abr(ani& animation, float dt, status& wizard);
void moving(ani& animation, float dt, status& wizard);


//1st item 
struct itemssssss
{
    int hp = 0;
    int mana = 0;
    int movement_speed = 0;

    int ability_haste = 0;
    int ability_power = 0;
    // Passive effect variables
    int auto_attack_count; // Counter for auto attacks (bullets)
    bool extra_damage_active; // Flag for extra damage from passive effect
    float extra_damege = 0;
    float auto_cool_down = 0;
    bool passive = false;
    bool isactive = false;
}items[4];

// NPC structure
struct npcs {
    RectangleShape enemy;
    unsigned health = 100;
    bool istimewarpon = false;
    float damage_done = 50;
} enemy;

// Map structure
struct map1 {
    RectangleShape ground;
} map2;

// Bullet structure
struct Bullet {
    CircleShape bullet;
    Vector2f bullet_velocity;
    float speed = 0.05f;
    float range = 350.f;
    Bullet(Vector2f position, Vector2f direction, float speed = 0.05f)
        : speed(speed) {
        bullet.setRadius(5.f);
        bullet.setFillColor(Color::Red);
        bullet.setPosition(position);
        bullet_velocity = direction * speed;
    }
};

vector<Bullet> bullets;
//set texture 
/*void set_texture(status& wizard) {

}*/

//statues calculation
void statues_calc() {
    wizard.autodamage = (wizard.autodamage) * (100 + wizard.abilitypower) / 100;
    wizard.fire_damage = (wizard.fire_damage) * (100 + wizard.abilitypower) / 100;
    wizard.flash_cooldown = (wizard.flash_cooldown) * (static_cast<float>(100) / 100 + wizard.abilityhaste);
    wizard.fire_cooldown = (wizard.fire_cooldown) * (static_cast<float>(100) / 100 + wizard.abilityhaste);
    wizard.time_warp_cooldown = (wizard.time_warp_cooldown) * (static_cast<float>(100) / 100 + wizard.abilityhaste);
}
// Function to handle movement of the main character
void handle_movement(status& wizard, float& velocity_y, bool& can_jump, bool& is_on_ground, float deltatime, float gravity, Clock& it, ani& animation) {

    //const float gravity = 100.0f;

    // Movement variables
    Vector2f movement(0, 0);

    // Check if the main character is on the ground
    is_on_ground = wizard.wizard.getGlobalBounds().intersects(map2.ground.getGlobalBounds());
    if (is_on_ground) {
        can_jump = true;
        velocity_y = 0; // Reset vertical velocity when on the ground
    }
    else {
        can_jump = false;
    }

    // Handle movement left and right
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        animation.lr = false;
        animation.u = 3;
        moving(animation, deltatime, wizard);
        movement.x = -wizard.movementspeed * deltatime;
        it.restart();
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {


        animation.lr = true;
        animation.u = 4;
        moving(animation, deltatime, wizard);
        movement.x = wizard.movementspeed * deltatime;
        it.restart();
    }

    // Handle jumping
    if (Keyboard::isKeyPressed(Keyboard::Space) && can_jump) {
        velocity_y = -sqrt(2 * gravity * 0.035f * 0.005f); // Apply jump velocity
        can_jump = false;
    }

    // Update character position based on movement and gravity
    wizard.wizard.move(movement.x, velocity_y);

    // Apply gravity
    velocity_y += gravity * deltatime * 0.005f;

    if (it.getElapsedTime().asSeconds() >= 1.0) {
        if (animation.lr == true) {
            animation.u = 2;
            idle(animation, deltatime, wizard);
        }

        else if (animation.lr == false)
        {

            animation.u = 14;
            idle(animation, deltatime, wizard);

        }
    }
}


// Function to normalize a vector
Vector2f normalize_vector(Vector2f vector) {
    float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);
    return vector / magnitude;
}

void first_item(status& wizard, int& counter) {
    //the statues
    if (items[0].isactive)
    {
        items[0].hp = 400;
        items[0].ability_haste = 20;
        items[0].ability_power = 50;
        counter++;
        if (counter == 1)
        {
            wizard.hp += items[0].hp;

            wizard.abilityhaste += items[0].ability_haste;

            wizard.abilitypower += items[0].ability_power;
        }
        //passive
        items[0].passive = true;
    }
}

void second_item(int& counter, Clock& passive_timer) {
    if (items[1].isactive)
    {
        items[1].hp = 600;
        items[1].mana = 300;
        items[1].movement_speed = 0.10f * wizard.movementspeed;
        items[1].ability_haste = 5;
        counter++;
        if (counter == 1)
        {
            wizard.hp += items[1].hp;
            wizard.mana += items[1].mana;
            wizard.movementspeed += items[1].movement_speed;
            wizard.abilityhaste += items[1].ability_haste;
        }
        //pasive
        items[1].passive = true;
        float total_damage = 0;
        if (items[1].passive)
        {
            //colision of enemy with wizard
            if (passive_timer.getElapsedTime().asSeconds() >= 2)
            {
                total_damage += enemy.damage_done;
                total_damage = total_damage * 0.05f;
                wizard.hp += total_damage;
            }
            passive_timer.restart();
        }
    }

}

// Function to handle shooting bullets
void shoot_bullet(Vector2f player_position, Vector2f mouse_position, Clock& cooldown_clock, float cooldown_duration) {

    // Check cooldown before shooting                    // Cooldown duration for shooting (in seconds)
    if (cooldown_clock.getElapsedTime().asSeconds() > cooldown_duration) {
        // Calculate the direction from the player's position to the mouse position
        Vector2f direction = mouse_position - player_position;
        direction = normalize_vector(direction); // Normalize the direction vector

        // Create a new bullet at the player's position with the calculated direction
        Bullet new_bullet(player_position, direction);
        if (items[0].passive)
        {
            items[0].auto_attack_count++;
            if (items[0].auto_attack_count % 4 == 0)
            {
                items[0].extra_damage_active = true;
            }
            else
            {
                items[0].extra_damage_active = false;
                items[0].extra_damege = 0;
            }
        }


        // Add the bullet to the list of bullets
        bullets.push_back(new_bullet);

        // Reset the cooldown clock
        cooldown_clock.restart();
    }
}


// Main character and ground initialization function
void main_character_and_ground() {
    // Initialize the main character (wizard)
    wizard.wizard.setPosition(Vector2f(120, 440));

    // Initialize the enemy (enemy)
    enemy.enemy.setSize(Vector2f(30, 50));
    enemy.enemy.setFillColor(Color::Magenta);
    enemy.enemy.setOutlineColor(Color::White);
    enemy.enemy.setOutlineThickness(1.5f);
    enemy.enemy.setPosition(Vector2f(400, 440));

    // Initialize the ground (map2)
    map2.ground.setSize(Vector2f(850, 40));
    map2.ground.setFillColor(Color::Red);
    map2.ground.setPosition(Vector2f(0, 570));
}

// Function to apply poison damage to the enemy
void poison(bool& ispoison, Clock& time, int& counter) {
    if (ispoison)
    {
        if (time.getElapsedTime().asSeconds() > 0.5 && counter <= 5)
        {
            enemy.health -= 0.02f * wizard.autodamage;
            counter++;
            if (counter == 5)
            {
                ispoison = false;
                counter = 0;
            }
            time.restart();
        }
    }
}

// Function to activate the Time Warp ability
void activate_time_warp(status& wizard, bool& istimewarpon, int& counter) {
    counter++;
    if (counter == 1 || wizard.time_warp_timer.getElapsedTime().asSeconds() > wizard.time_warp_cooldown) {
        // Activate the ability and reset the timer
        wizard.time_warp_active = true;
        if (counter == 1)
        {
            wizard.mana -= 100;
        }
        istimewarpon = true;
        wizard.time_warp_timer.restart();
    }
}

// Function to handle the effects of Time Warp
void handle_time_warp(status& wizard, npcs& enemy, float deltatime, bool& istimewarpon, int& counter) {
    if (wizard.time_warp_active) {
        // Slow down the enemy's movement speed
        enemy.enemy.move(0, 0); // Stop all movements for enemies

        // Reduce the enemy's movement speed by the slowdown factor
        Vector2f enemy_velocity(0.f, 0.f);

        // Move the enemy using the adjusted velocity
        enemy.enemy.move(enemy_velocity);

        // Check if the ability duration has ended
        if (wizard.time_warp_timer.getElapsedTime().asSeconds() > wizard.time_warp_duration) {
            // Deactivate the ability
            wizard.time_warp_active = false;
            counter = 0;
            istimewarpon = false;
        }
    }
}


void handle_movement_enemy(npcs& enemy, float& velocity_y, bool& is_on_ground, float deltatime, float gravity, bool& istimewarbon) {

    //const float gravity = 100.0f;

    // Movement variables
    Vector2f movement(0, 0);

    // Check if the main character is on the ground
    is_on_ground = enemy.enemy.getGlobalBounds().intersects(map2.ground.getGlobalBounds());
    if (is_on_ground) {
        //can_jump = true;
        velocity_y = 0; // Reset vertical velocity when on the ground
    }
    else {
        //can_jump = false;
    }
    if (istimewarbon)
    {
        enemy.enemy.move(0, 0);
    }
    else
    {
        // Handle movement left and right
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            movement.x = -wizard.movementspeed * deltatime;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            movement.x = wizard.movementspeed * deltatime;
        }
    }

    // Handle jumping
    /*if (Keyboard::isKeyPressed(Keyboard::Space) && can_jump) {
        velocity_y = -sqrt(2 * gravity * 0.035f * 0.005f); // Apply jump velocity
        can_jump = false;
    }*/

    // Update character position based on movement and gravity
    enemy.enemy.move(movement.x, velocity_y);

    // Apply gravity
    velocity_y += gravity * deltatime * 0.005f;
}


void flash_ability(status& wizard, int& counter) {
    // Check if the flash cooldown has elapsed
    counter++;
    if (counter == 1 || wizard.flash_timer.getElapsedTime().asSeconds() > wizard.flash_cooldown) {
        // Calculate the flash direction based on the wizard's facing direction
        // You can define the facing direction as the movement direction (left or right)
        float flash_direction = Keyboard::isKeyPressed(Keyboard::Right) ? 1.0f : -1.0f;

        // Calculate the new position after flashing
        Vector2f new_position = wizard.wizard.getPosition() + Vector2f(flash_direction * wizard.flash_distance, 0);

        // Move the wizard to the new position
        wizard.wizard.setPosition(new_position);

        // Reset the flash timer
        wizard.flash_timer.restart();
    }
}

void activate_fire_ability(status& wizard, npcs& enemy, Clock& firetime, int& counter, bool& isfire, bool is_on_ground, int& counter_of_mana) {
    // Check if the fire ability is available based on its cooldown
    /*if (wizard.fire_timer.getElapsedTime().asSeconds() > wizard.fire_cooldown) {
        // Activate the fire ability
        wizard.fire_active = true;
        wizard.fire_timer.restart();
    }*/
    wizard.fire_active = true;
    // If the fire ability is active
    counter_of_mana++;
    if (counter_of_mana == 1 || wizard.fire_active && is_on_ground && wizard.fire_timer.getElapsedTime().asSeconds() > wizard.fire_cooldown) {

        if (counter_of_mana == 1)
        {
            wizard.mana -= 50;
        }
        if (firetime.getElapsedTime().asSeconds() > 0.5 && counter <= 5)
        {
            counter++;
            enemy.health -= wizard.fire_damage;
            if (counter == 5)
            {
                wizard.fire_active = false;
                counter = 0;
                isfire = false;
                counter_of_mana = 0;
                wizard.fire_timer.restart();
            }
            firetime.restart();
        }
    }
}




int main() {
    // Create a window
    RenderWindow window(VideoMode(800, 600), "SFML Example");

    Clock it;

    // Initialize the main character and ground
    main_character_and_ground();
    //set_texture(wizard);
    wizard.wiz_tx.loadFromFile("C:\\Users\\Seif2\\source\\repos\\ConsoleApplication10\\ConsoleApplication10\\wiz.png");
    wizard.wizard.setTexture(wizard.wiz_tx);
    wizard.wizard.setTextureRect(IntRect(0, 0, 96, 98));

    // Clock to manage shooting cooldown
    Clock cooldown_clock;

    // Gravity and movement settings
    const float gravity = 100.0f;
    float velocity_y = 0;
    float velocity_y_enemy = 0;
    bool can_jump = false;
    bool is_on_ground = false;
    bool ispoison = false;
    bool isfire = false;

    int items_statues_counter = 0;
    int abilit_1 = 0;
    int ultimate = 0;
    int flash = 0;
    int bullet_counter = 0;
    // Clock to track game time
    Clock gametime;

    Clock time;

    Clock tfisrt;

    Clock shockWaveClock; // Clock to manage shock wave cooldown

    Clock firetime;

    Clock second_item_passive;
    int second_item_counter = 0;

    int counter = 1;

    int counter_fire = 1;
    Clock poison_timer;
    float t = 0;
    float deltatime = 0;
    // Game loop
    while (window.isOpen()) {
        // Event handling
        Event event;
        gametime.restart();
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::T)) {
            activate_time_warp(wizard, enemy.istimewarpon, ultimate);
        }

        if (Keyboard::isKeyPressed(Keyboard::V)) {
            isfire = true;
        }
        if (isfire)
        {
            activate_fire_ability(wizard, enemy, firetime, counter_fire, isfire, is_on_ground, abilit_1);
        }
        if (Keyboard::isKeyPressed(Keyboard::K))
        {
            items[0].isactive = true;
        }
        first_item(wizard, items_statues_counter);
        if (Keyboard::isKeyPressed(Keyboard::L))//the place of the technique will be used
        {
            items[1].isactive = true;
        }
        second_item(second_item_counter, second_item_passive);

        // Handle the effects of Time Warp ability
        handle_time_warp(wizard, enemy, deltatime, enemy.istimewarpon, ultimate);

        // Handle movement
        handle_movement(wizard, velocity_y, can_jump, is_on_ground, deltatime, gravity, it, animation);



        if (Keyboard::isKeyPressed(Keyboard::B)) {
            flash_ability(wizard, flash);
        }


        handle_movement_enemy(enemy, velocity_y_enemy, is_on_ground, deltatime, gravity, enemy.istimewarpon);

        // Handle shooting bullets
        Vector2f player_center = wizard.wizard.getPosition();
        Vector2f mouse_position = Vector2f(Mouse::getPosition(window));
        if (Mouse::isButtonPressed(Mouse::Left)) {
            shoot_bullet(player_center, mouse_position, cooldown_clock, wizard.auto_cooldown_duration);
        }

        // Update bullets' positions and manage them
        for (size_t i = 0; i < bullets.size(); ) {
            bullets[i].bullet.move(bullets[i].bullet_velocity);

            // Calculate distance traveled
            float distance = sqrt(pow(bullets[i].bullet.getPosition().x - player_center.x, 2) +
                pow(bullets[i].bullet.getPosition().y - player_center.y, 2));

            // Check if the bullet exceeds its range or hits the enemy
            bool is_hit = bullets[i].bullet.getGlobalBounds().intersects(enemy.enemy.getGlobalBounds());

            // Remove bullet if it exceeds range or hits the enemy
            if (distance > bullets[i].range || is_hit) {
                if (is_hit) {

                    if (items[0].extra_damage_active)
                    {
                        items[0].extra_damege = 0.05f * wizard.autodamage;
                    }
                    enemy.health -= wizard.autodamage + items[0].extra_damege;
                    ispoison = true;
                }
                bullets.erase(bullets.begin() + i);
            }
            else {
                i++;
            }
        }
        //poison effect
        //poison(ispoison, time, counter);
        //cout << enemy.health << endl;
        //cout << wizard.hp << endl;




        // Clear the window
        window.clear();

        // Draw bullets
        for (const Bullet& bullet : bullets) {
            window.draw(bullet.bullet);
        }

        // Draw ground
        window.draw(map2.ground);

        // Draw the wizard and enemy
        window.draw(wizard.wizard);
        window.draw(enemy.enemy);
        // Display the content of the window
        window.display();

        deltatime = gametime.getElapsedTime().asSeconds();

    }

    return 0;
}

void idle(ani& animation, float dt, status& wizard) {


    if (animation.timer < 0) {
        animation.i++;
        if (animation.i >= 6)
            animation.i = 0;
        wizard.wizard.setTextureRect(IntRect((animation.i * 96), (animation.u * 99), 96, 98));
        animation.timer = animation.delay;


    }
    else {
        animation.timer -= dt;
    }
}


void ab(ani& animation, float dt, status& wizard) {


    if (animation.timer < 0) {
        animation.i++;
        if (animation.i >= 6) {


            animation.aq = false;
            animation.i = 0;

        }

        wizard.wizard.setTextureRect(IntRect((animation.i * 96), (animation.u * 98.4), 96, 98));
        animation.timer = animation.delayq;


    }
    else {
        animation.timer -= dt;
    }
}

void abe(ani& animation, float dt, status& wizard) {


    if (animation.timer < 0) {
        animation.i++;

        if (animation.i >= 8) {
            animation.ae = false;
            animation.i = 0;
        }

        wizard.wizard.setTextureRect(IntRect((animation.i * 96), (animation.u * 98), 96, 98));
        animation.timer = animation.delayq;


    }
    else {
        animation.timer -= dt;
    }
}
void moving(ani& animation, float dt, status& wizard) {


    if (animation.timer < 0) {
        animation.i++;
        animation.i = animation.i % 6;
        wizard.wizard.setTextureRect(IntRect((animation.i * 96.15), (animation.u * 98), 96, 98));
        animation.timer = animation.delaym;


    }
    else {
        animation.timer -= dt;
    }
}
void abw(ani& animation, float dt, status& wizard) {


    if (animation.timer < 0) {
        animation.i++;
        if (animation.i >= 7) {


            animation.aw = false;
            animation.i = 0;
        }


        wizard.wizard.setTextureRect(IntRect((animation.i * 96), (animation.u * 99.2), 96, 98));
        animation.timer = animation.delayq;


    }
    else {
        animation.timer -= dt;
    }
}
void abr(ani& animation, float dt, status& wizard) {


    if (animation.timer < 0) {
        animation.i++;

        if (animation.i >= 16) {
            animation.ar = false;
            animation.i = 0;
        }

        wizard.wizard.setTextureRect(IntRect((animation.i * 96), (animation.u * 98), 96, 98));
        animation.timer = animation.delayq;


    }
    else {
        animation.timer -= dt;
    }
}