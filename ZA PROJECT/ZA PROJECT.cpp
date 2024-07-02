#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

struct status {
    Sprite wizard;
    Texture wiz_tx;
    int max_hp = 1000;
    float hp = max_hp;
    int max_mana = 400;
    float mana = max_mana;
    float level = 0;
    float current_level;
    int enemy_death_counter = 4;
    int enemy_death_counter_for_show = enemy_death_counter;
    int the_divisor = 5;
    float movementspeed = 200.f;
    float abilitypower = 20;
    float abilityhaste = 0;
    float dash = 50.f;
    float autodamage = 20.f;
    float auto_cooldown_duration = 1.f;
    float time_warp_cooldown = 50.0f;  // Cooldown duration (in seconds)
    float time_warp_duration = 20.0f;  // Effect duration (in seconds)
    float time_warp_slowdown_factor = 0.05f;  // Slowdown factor (e.g., 0.5 = half speed)
    bool time_warp_active = false;  // Whether the ability is active
    Clock time_warp_timer;  // Timer to manage ability duration and cooldown
    float flash_distance = 200.0f; // Distance for the flash ability (in pixels)
    float flash_cooldown = 8.0f; // Cooldown duration for the flash ability (in seconds)
    Clock flash_timer; // Timer to manage flash ability cooldown
    float fire_damage = 50.0f; // Damage per second to the enemy
    float fire_duration = 5.0f; // Duration of the fire (in seconds)
    float fire_cooldown = 15.0f; // Cooldown duration for the fire ability (in seconds)
    Clock fire_timer; // Timer to manage the ability duration and cooldown
    bool fire_active = false; // Whether the fire ability is active
    bool isfire = false;
    Clock heal;
    float heal_health = 100.f;
    float heal_cooldown = 20;
    bool timerq = false, timerR = false, timerf = false, timerw = false;
    bool if_levelup = false;
    bool ishit = false;
    bool back_ability = false;
}wizard;


//sounds
struct SOUNd
{
    SoundBuffer main_menu;
    Sound mainMenu;

    SoundBuffer back_sound;
    Sound backSound;

    SoundBuffer bullet_sound;
    Sound bulletSound;

    SoundBuffer ability_1;
    Sound ability1;

    SoundBuffer ability_2;
    Sound ability2;

    SoundBuffer ability_3;
    Sound ability3;

    SoundBuffer ability_4;
    Sound ability4;

    SoundBuffer jump_sound;
    Sound jumpSound;

    SoundBuffer levelup;
    Sound levelup_sound;

    SoundBuffer use_item;
    Sound useItem;

    SoundBuffer paused_sound;
    Sound pausedSound;

    SoundBuffer unpaused_sound;
    Sound unpausedSound;

    SoundBuffer hover;
    Sound hover_sound;

    //boss
    SoundBuffer boss_hit;
    Sound bossHit;

    SoundBuffer boss_ability1;
    Sound bossAbility1;

    SoundBuffer boss_Ability2;
    Sound bossAbility2;

    SoundBuffer boss_death;
    Sound bossDeath;
}sound;

//function sound
void SOUND(SOUNd& sound) {
    //music
    sound.main_menu.loadFromFile("./assets/music/music/music/videoplayback(7).wav");
    sound.mainMenu.setBuffer(sound.main_menu);
    sound.mainMenu.setVolume(40);
    sound.mainMenu.setLoop(true);
    sound.mainMenu.play();

    sound.back_sound.loadFromFile("./assets/music/music/music/videoplayback (11).wav");
    sound.backSound.setBuffer(sound.back_sound);
    sound.backSound.setVolume(50);
    sound.backSound.setLoop(true);
    sound.backSound.play();
    //bullet
    sound.bullet_sound.loadFromFile("./assets/music/music/sound effect/bulllet.wav");
    sound.bulletSound.setBuffer(sound.bullet_sound);
    sound.bulletSound.setVolume(150);
    //ability1
    sound.ability_1.loadFromFile("./assets/music/sukuna.wav");
    sound.ability1.setBuffer(sound.ability_1);
    sound.ability1.setVolume(90);
    //ability2
    sound.ability_2.loadFromFile("./assets/music/heal.wav");
    sound.ability2.setBuffer(sound.ability_2);
    sound.ability2.setVolume(90);
    //ability3
    sound.ability_3.loadFromFile("./assets/music/music/sound effect/ability 3.wav");
    sound.ability3.setBuffer(sound.ability_3);
    sound.ability3.setVolume(90);
    //ability4
    sound.ability_4.loadFromFile("./assets/music/fire.wav");
    sound.ability4.setBuffer(sound.ability_4);
    sound.ability4.setVolume(90);
    //jump
    sound.jump_sound.loadFromFile("./assets/music/music/sound effect/30_Jump_03.wav");
    sound.jumpSound.setBuffer(sound.jump_sound);
    sound.jumpSound.setVolume(150);
    //levelup
    sound.levelup.loadFromFile("./assets/music/music/sound effect/48_Speed_up_02.wav");
    sound.levelup_sound.setBuffer(sound.levelup);
    sound.levelup_sound.setVolume(90);
    //use item
    sound.use_item.loadFromFile("./assets/music/music/sound effect/051_use_item_01.wav");
    sound.useItem.setBuffer(sound.use_item);
    sound.useItem.setVolume(80);
    //paused
    sound.paused_sound.loadFromFile("./assets/music/music/sound effect/092_Pause_04.wav");
    sound.pausedSound.setBuffer(sound.paused_sound);
    sound.pausedSound.setVolume(80);
    //paused
    sound.unpaused_sound.loadFromFile("./assets/music/music/sound effect/098_Unpause_04.wav");
    sound.unpausedSound.setBuffer(sound.unpaused_sound);
    sound.unpausedSound.setVolume(80);
    //hover
    sound.hover.loadFromFile("./assets/music/music/sound effect/001_Hover_01.wav");
    sound.hover_sound.setBuffer(sound.hover);
    sound.hover_sound.setVolume(60);

    //boss
    sound.boss_hit.loadFromFile("./assets/music/08_Bite_04.wav");
    sound.bossHit.setBuffer(sound.boss_hit);
    sound.bossHit.setVolume(60);
    //bossability1
    sound.boss_ability1.loadFromFile("./assets/music/04_Fire_explosion_04_medium.wav");
    sound.bossAbility1.setBuffer(sound.boss_ability1);
    sound.bossAbility1.setVolume(90);
    //bossability2
    sound.boss_Ability2.loadFromFile("./assets/music/04_Fire_explosion_04_medium.wav");
    sound.bossAbility2.setBuffer(sound.boss_Ability2);
    sound.bossAbility2.setVolume(90);
    //bossdeath
    sound.boss_death.loadFromFile("./assets/music/10_human_special_atk_1.wav");
    sound.bossDeath.setBuffer(sound.boss_death);
    sound.bossDeath.setVolume(150);
}


//animation
struct ani
{
    int i = 0, u, i_jump = 0, i_damge = 0, u_damage = 0;
    float timer = 0;
    float delay = .2; float delayq = .1, delaym = .1, delay_jump = 0.05;
    bool aq = false, ae = false, ar = false, aw = false, lr = true, motion_right = false, death = false, damage = false, idel = false
        , moving = false;
    Clock qab;
    Clock eab;
    Clock rab;
    Clock wab;

}animation;

void idle(ani& animation, float dt, status& wizard, bool can_jump);
void ab(ani& animation, float dt, status& wizard);
void abe(ani& animation, float dt, status& wizard);
void abw(ani& animation, float dt, status& wizard);

void abr(ani& animation, float dt, status& wizard);
void moving(ani& animation, float dt, status& wizard);

void death_ani(ani& animation, float dt, status& wizard);

void jump_animation(ani& animation, float dt, status& wizard, Clock& jump_clock, bool on_ground, int& jump_counter);

void get_damaged(ani& animation, float dt, status& wizard);

//boss
const int Window_width = 1200;
const int Window_height = 800;
const float w_boss = 64;
const float h_boss = 64;
const float fire_rate = 0.5;
const float fireBall_rate = 10;
const float ability2 = 17.5;
const int bullet_speed = 300.f;
const float ch_speed = 150;
const float boss_speed = 0.8f;
const float min_distance_to_main = 150.f;
const float gravity = 300;
const float floorHeight = 100.0f;
const int maxBullets = 5;
////////////////////////////////
const float shooting_ability = 5;
const float abilityb2 = 8.5;
const float distance_to_hit = 40.f;
bool mappp = true;
///////////////////////////////////
enum BossState
{
    Standing,
    Moving,
    Shooting,
    Ability_1,
    Ability_2,
    Dead
};

struct Boss
{
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Texture standingTexture;
    sf::Texture movingTexture;
    sf::Texture shootingTexture;
    sf::Texture ability_1Texture;
    BossState state;
    int currentFrame;
    float frameDuration;
    float elapsedTime;
    float Health = 2000;
};



struct Bullllllet
{
    sf::Sprite shape;
    sf::Vector2f direction;
    sf::Clock timer;
    sf::Texture bulletTexture;
    float currentFrame;
};



//struct MainCharacter
//{
//    sf::RectangleShape shape;
//    sf::Vector2f velocity;
//    float speed;
//    float Health = 2000;
//};

struct Fireball
{
    sf::Sprite shape;
    sf::Vector2f velocity;
    sf::Clock cooldownTimer;
    sf::Texture AbilityTexture;
    int currentFrame;
    bool active = false;
};

struct Ability2
{
    sf::Sprite shape;
    sf::Vector2f velocity;
    sf::Clock cooldownTimer;
    sf::Texture AbilityTexture;
    int currentFrame;
    bool active = false;
};

void SetupBoss(Boss& boss, status& character)
{
    boss.standingTexture.loadFromFile("./assets/BossIdel.png");
    boss.movingTexture.loadFromFile("./assets/BossMove.png");
    boss.shootingTexture.loadFromFile("./assets/Boss_shooting.png");
    boss.ability_1Texture.loadFromFile("./assets/bossAbility.png");

    boss.shape.setSize(sf::Vector2f(w_boss, h_boss));
    boss.shape.setPosition(9127, 850);
    boss.shape.setScale(6.f, 6.f);

    boss.state = BossState::Standing;

    boss.currentFrame = 0;
    boss.frameDuration = 0.1258f; // Adjust this value according to your animation speed
    boss.elapsedTime = 0.f;

    boss.shape.setTexture(&boss.standingTexture);
}

void setupBullet(Bullllllet& bullet)
{
    bullet.bulletTexture.loadFromFile("./assets/bullet.png");

    bullet.shape.setTexture(bullet.bulletTexture);
    bullet.shape.setTextureRect(sf::IntRect(0, 0, 33.8, 15)); // Set initial frame
    bullet.currentFrame = 0;
}

void setupFireball(Fireball& fireball)
{
    fireball.AbilityTexture.loadFromFile("./assets/fire_ball.png");
    fireball.shape.setTextureRect(sf::IntRect(0, 0, 31.875, 25));
    fireball.currentFrame = 0;
}

void setupAbility2(Ability2& ability)
{
    ability.AbilityTexture.loadFromFile("./assets/ability2.png");
    ability.shape.setTextureRect(sf::IntRect(0, 0, 97, 34));
    ability.currentFrame = 0;
}

void animateBoss(Boss& boss, status& character, float deltaTime)
{
    float distanceToMain = sqrt(pow(character.wizard.getPosition().x - boss.shape.getPosition().x, 2) +
        pow(character.wizard.getPosition().y - boss.shape.getPosition().y, 2));

    static sf::Clock animation_bullets;
    static sf::Clock animation_ability_1;
    static sf::Clock animation_ability_2;

    //sf::Clock idle_clock;
    bool shooting = 0;
    bool ability_1 = 0;
    bool ability_2 = 0;

    if (animation_ability_2.getElapsedTime().asSeconds() >= ability2)
    {

        boss.state = BossState::Ability_2;
        if (animation_ability_2.getElapsedTime().asSeconds() >= boss.frameDuration * 13 + ability2)
            animation_ability_2.restart();
    }
    else if (animation_ability_1.getElapsedTime().asSeconds() >= fireBall_rate and !ability_2)
    {
        boss.state = BossState::Ability_1;
        if (animation_ability_1.getElapsedTime().asSeconds() >= boss.frameDuration * 13 + fireBall_rate)
            animation_ability_1.restart();
    }
    else if (animation_bullets.getElapsedTime().asSeconds() >= fire_rate and !ability_1 and !ability_2)
    {
        boss.state = BossState::Shooting;
        if (animation_bullets.getElapsedTime().asSeconds() >= boss.frameDuration * 4 + fire_rate)
            animation_bullets.restart();
        //idle_clock.restart();
    }
    else if (distanceToMain <= min_distance_to_main /* and idle_clock.getElapsedTime().asSeconds() > 1 */)
    {
        boss.state = BossState::Standing;
    }
    else
    {
        if (!shooting and !ability_1 and !ability_2)
        {
            boss.state = BossState::Moving;
            //idle_clock.restart();
        }
    }

    sf::Vector2f direction = character.wizard.getPosition() - boss.shape.getPosition();

    if (direction.x < 0)
    {
        boss.shape.setScale(-5.f, 5.f);
        boss.shape.setOrigin(w_boss / 2.f, 0);
    }
    else
    {
        boss.shape.setScale(5.f, 5.f);
        boss.shape.setOrigin(w_boss / 2.f, 0);
    }


    switch (boss.state)
    {
    case BossState::Standing:
        boss.shape.setTexture(&boss.standingTexture);
        break;
    case BossState::Moving:
        boss.shape.setTexture(&boss.movingTexture);
        break;
    case BossState::Shooting:
        boss.shape.setTexture(&boss.shootingTexture);
        shooting = 1;
        break;
    case BossState::Ability_1:
        boss.shape.setTexture(&boss.ability_1Texture);
        ability_1 = 1;
        break;
    case BossState::Ability_2:
        boss.shape.setTexture(&boss.ability_1Texture);
        ability_2 = 1;
        break;
    }

    boss.elapsedTime += deltaTime;

    if (boss.state == BossState::Ability_1 || boss.state == BossState::Ability_2)
    {
        static sf::Clock fireB;

        if (fireB.getElapsedTime().asSeconds() >= 0.25)
        {
            boss.currentFrame += 1;

            if (boss.currentFrame >= 13)
            {
                boss.currentFrame = 0;
            }
            boss.shape.setTextureRect(sf::IntRect((int)boss.currentFrame * w_boss, 0, w_boss, h_boss));
            fireB.restart();
        }
    }
    else
    {
        static sf::Clock fireB;

        if (fireB.getElapsedTime().asSeconds() >= 0.125)
        {
            boss.currentFrame += 1;

            if (boss.currentFrame >= 4)
            {
                boss.currentFrame = 0;
            }
            boss.shape.setTextureRect(sf::IntRect((int)boss.currentFrame * w_boss, 0, w_boss, h_boss));
            fireB.restart();
        }
    }
}

void animateBullet(Bullllllet& bullet)
{
    bullet.currentFrame += 0.5;
    if (bullet.currentFrame >= 5)
    {
        bullet.currentFrame = 0;
    }
    bullet.shape.setTextureRect(sf::IntRect((int)bullet.currentFrame * 33.8, 0, 33.8, 15));
}

void animateAbility2(Ability2& ability)
{
    static sf::Clock ability2Clock;

    if (ability2Clock.getElapsedTime().asSeconds() >= 0.2)
    {
        ability.currentFrame += 1;

        if (ability.currentFrame >= 4)
        {
            ability.currentFrame = 0;
        }

        ability.shape.setTextureRect(sf::IntRect((int)ability.currentFrame * 97, 0, 97, 34));
        ability2Clock.restart();
    }
}

void animateFireBall(Fireball& fireball, Boss& boss)
{
    static sf::Clock fireB;

    if (fireB.getElapsedTime().asSeconds() >= 0.2)
    {
        fireball.currentFrame += 1;

        if (fireball.currentFrame >= 8)
        {
            fireball.currentFrame = 4;
        }
        fireball.shape.setTextureRect(sf::IntRect((int)fireball.currentFrame * 31.875, 0, 33.875, 22));
        fireB.restart();
    }
}

void updateAbility2(Ability2& ability, status& character, float deltaTime)
{
    if (ability.active)
    {
        ability.shape.move(ability.velocity * deltaTime);

        if (ability.shape.getGlobalBounds().intersects(character.wizard.getGlobalBounds()))
        {
            animation.damage = true;
            if (animation.damage)
            {
                if (animation.lr)
                {
                    animation.u_damage = 0;
                }
                else
                {
                    animation.u_damage = 8;
                }
            }
            character.hp -= .18;
            ability.active = false;
        }


        if (ability.shape.getPosition().x < 0 || ability.shape.getPosition().x > Window_width ||
            ability.shape.getPosition().y < 0 || ability.shape.getPosition().y > Window_height)
        {
            ability.active = false;
        }
    }
}

void updateFireball(Fireball& fireball, status& character, float deltaTime)
{
    if (fireball.active)
    {
        fireball.shape.move(fireball.velocity * deltaTime);

        if (fireball.shape.getGlobalBounds().intersects(character.wizard.getGlobalBounds()))
        {
            animation.damage = true;
            if (animation.damage)
            {
                if (animation.lr)
                {
                    animation.u_damage = 0;
                }
                else
                {
                    animation.u_damage = 8;
                }
            }
            character.hp -= 200;
            fireball.active = false;
        }
    }
}

void moveBoss(Boss& boss, status& character, float deltaTime, bool& boss_moving, Sprite& wizard, bool& wiz_in_area)
{
    if (boss.state != BossState::Ability_1 and boss.state != BossState::Ability_2)
    {
        sf::Vector2f direction = character.wizard.getPosition() - boss.shape.getPosition();
        float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
        sf::Vector2f normalizedDirection = direction / length;

        boss.velocity = normalizedDirection * boss_speed * deltaTime * ch_speed;
        if (boss_moving == true && wizard.getPosition().x > 8300 && wizard.getPosition().x < 10300)
        {
            wiz_in_area = true;
            if (length <= min_distance_to_main)
            {
                boss.velocity = sf::Vector2f(0.f, 0.f);
            }

            boss.velocity.y += gravity * deltaTime;

            boss.shape.move(boss.velocity);
        }
    }

    if (boss.shape.getPosition().y + boss.shape.getSize().y > Window_height - floorHeight)
    {
        boss.shape.setPosition(boss.shape.getPosition().x, Window_height - floorHeight - boss.shape.getSize().y);
        boss.velocity.y = 0;
    }

    if (boss.shape.getPosition().x < 8400)
    {
        boss.shape.setPosition(0, boss.shape.getPosition().y);
    }
    //10377.5\805
    if (boss.shape.getPosition().x + boss.shape.getSize().x > 10300)
    {
        boss.shape.setPosition(10300 - boss.shape.getSize().x, boss.shape.getPosition().y);
    }
}

//void moveMainCharacter(status& character, float deltaTime)
//{
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
//    {
//        character.velocity.x = -character.speed * deltaTime;
//    }
//    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
//    {
//        character.velocity.x = character.speed * deltaTime;
//    }
//    else
//    {
//        character.velocity.x = 0;
//        character.velocity.y = gravity * deltaTime;
//    }
//
//    character.shape.move(character.velocity);
//
//    if (character.shape.getPosition().y + character.shape.getSize().y > Window_height - floorHeight)
//    {
//        character.shape.setPosition(character.shape.getPosition().x, Window_height - floorHeight - character.shape.getSize().y);
//        character.velocity.y = 0;
//    }
//}

void fireBullet(Bullllllet* bullets, int& numBullets, Boss& boss, status& character, float deltaTime, int currentFrame)
{
    static sf::Clock fireClock;
    Bullllllet bullet;
    setupBullet(bullet);
    // Fire bullets when boss is in shooting state and at the right frame of the shooting animation
    if (fireClock.getElapsedTime().asSeconds() >= fire_rate and boss.currentFrame == 2 and boss.state == BossState::Shooting)
    {
        fireClock.restart();

        // Calculate aim direction based on character position and boss position
        sf::Vector2f aimDir = character.wizard.getPosition() - boss.shape.getPosition();
        aimDir.y -= h_boss / 2;
        float length = sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
        sf::Vector2f aimDirNorm = aimDir / length;

        bullet.shape.setPosition(boss.shape.getPosition().x, boss.shape.getPosition().y + h_boss / 6);

        if (aimDir.x < 0)
        {
            bullet.shape.setScale(2.f, 2.f);
            bullet.shape.setOrigin(w_boss / 1.5f, 0);
        }
        else
        {
            bullet.shape.setScale(-2.f, 2.f);
            bullet.shape.setOrigin(w_boss / 1.5f, 0);
        }
        bullet.timer.restart();
        bullet.direction = aimDirNorm;
        bullets[numBullets] = bullet;
        numBullets++;
    }

    // Update bullets' positions and check for collisions
    for (size_t i = 0; i < numBullets; i++)
    {
        float bulletSpeedX = bullet_speed * bullets[i].direction.x;
        float bulletSpeedY = bullet_speed * bullets[i].direction.y;
        bullets[i].shape.move(bulletSpeedX * deltaTime, bulletSpeedY * deltaTime);
        Vector2f boss_center = Vector2f(boss.shape.getPosition());
        float distance = sqrt(pow(bullets[i].shape.getPosition().x - boss_center.x, 2) +
            pow(bullets[i].shape.getPosition().y - boss_center.y, 2));
        if (/*bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > Window_width ||
            bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > Window_height*/distance > 500.f)
        {
            for (int j = i; j < numBullets - 1; j++)
            {
                bullets[j] = bullets[j + 1];
            }
            numBullets--;
            i--;
        }

        if (bullets[i].shape.getGlobalBounds().intersects(character.wizard.getGlobalBounds()))
        {
            animation.damage = true;
            if (animation.damage)
            {
                if (animation.lr)
                {
                    animation.u_damage = 0;
                }
                else
                {
                    animation.u_damage = 8;
                }
            }
            character.hp -= 50;
            for (int j = i; j < numBullets - 1; j++)
            {
                bullets[j] = bullets[j + 1];
            }
            numBullets--;
            i--;
        }
        //sound.bossHit.play();
    }
}

void fireBigFireball(Fireball& fireball, Boss& boss, status& character)
{
    if (fireball.cooldownTimer.getElapsedTime().asSeconds() >= fireBall_rate and boss.currentFrame == 8 and boss.state == BossState::Ability_1)
    {
        setupFireball(fireball);
        fireball.cooldownTimer.restart();

        sf::Vector2f direction = character.wizard.getPosition() - boss.shape.getPosition();
        sf::Vector2f normalizedDirection;
        fireball.shape.setPosition(boss.shape.getPosition().x, boss.shape.getPosition().y);

        if (direction.x < 0)
        {
            normalizedDirection = { -1.0f, 0.0f };
            fireball.shape.setScale(-8.f, 8.f);
            fireball.shape.setOrigin(w_boss / 2.5f, -12);
        }
        else
        {
            normalizedDirection = { 1.0f, 0.0f };
            fireball.shape.setScale(8.f, 8.f);
            fireball.shape.setOrigin(w_boss / 2.5f, -12);
        }
        fireball.velocity.x = normalizedDirection.x * bullet_speed;
        fireball.velocity.y = normalizedDirection.y * bullet_speed;

        fireball.active = true;
    }
    //sound.bossAbility1.play();
}

void activateAbility2(Ability2& ability, Boss& boss, status& character)
{
    if (ability.cooldownTimer.getElapsedTime().asSeconds() >= ability2 and boss.currentFrame == 8 and boss.state == BossState::Ability_2)
    {
        ability.active = true;

        setupAbility2(ability);
        ability.cooldownTimer.restart();

        sf::Vector2f direction = character.wizard.getPosition() - boss.shape.getPosition();
        sf::Vector2f normalizedDirection;

        ability.shape.setPosition(boss.shape.getPosition().x, boss.shape.getPosition().y);

        if (direction.x < 0)
        {
            normalizedDirection = { -1.0f, 0.0f };
            ability.shape.setScale(-4.f, 4.f);
            ability.shape.setOrigin(w_boss / 1.5f, -h_boss / 2.4);
        }
        else
        {
            normalizedDirection = { 1.0f, 0.0f };
            ability.shape.setScale(4.f, 4.f);
            ability.shape.setOrigin(w_boss / 1.5f, -h_boss / 2.4);
        }
        ability.velocity.x = normalizedDirection.x * bullet_speed;
        ability.velocity.y = normalizedDirection.y * bullet_speed;


    }
}
////////////////////////////////////////////
enum Boss2State
{
    Standing2,
    Moving2,
    hitting2,
    Ability_12,
    Ability_22,
    Dead2
};
struct Boss2
{
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Texture standingTexture;
    sf::Texture movingTexture;
    sf::Texture shootingTexture;
    sf::Texture ability_1Texture;
    sf::Texture ability_2Texture;

    Boss2State state;
    int currentFrame;
    float frameDuration;
    float Health = 2000;
};
struct Ability
{
    sf::Sprite shape;
    sf::Vector2f velocity;
    sf::Clock cooldownTimer;
    sf::Texture AbilityTexture;
    int currentFrame;
    bool active = false;
};
struct Abilityb2
{
    sf::Sprite shape;
    sf::Vector2f velocity;
    sf::Clock cooldownTimer;
    sf::Texture AbilityTexture;
    int currentFrame;
    bool active = false;
    sf::Vector2f position;
};
void SetupBoss2(Boss2& boss, status& character)
{
    boss.standingTexture.loadFromFile("./assets/idle.png");
    boss.movingTexture.loadFromFile("./assets/run.png");
    boss.shootingTexture.loadFromFile("./assets/attack.png");
    boss.ability_1Texture.loadFromFile("./assets/shoot.png");
    boss.ability_2Texture.loadFromFile("./assets/fly down.png");

    boss.shape.setSize(sf::Vector2f(w_boss, h_boss));
    boss.shape.setPosition(12000, 100);

    boss.state = Boss2State::Standing2;

    boss.currentFrame = 0;

    boss.shape.setTexture(&boss.standingTexture);
}
void setupability_1(Ability& fireball)
{
    fireball.AbilityTexture.loadFromFile("./assets/ability_b2.png");
    fireball.shape.setTextureRect(sf::IntRect(0, 0, 42, 34));
    fireball.currentFrame = 0;
}

void setupability_2(Abilityb2& poison)
{
    poison.AbilityTexture.loadFromFile("./assets/ability2_b2.png");
    poison.shape.setTextureRect(sf::IntRect(0, 0, 48, 64));
    poison.currentFrame = 0;
}

void animateBoss2(Boss2& boss, status& character, float deltaTime)
{
    float distanceToMain = sqrt(pow(character.wizard.getPosition().x - boss.shape.getPosition().x, 2) +
        pow(character.wizard.getPosition().y - boss.shape.getPosition().y, 2));

    static sf::Clock animation_hitting;
    static sf::Clock animation_ability_1;
    static sf::Clock animation_ability_2;

    bool hitting = 0;
    bool ability_1 = 0;
    bool ability_2 = 0;
    static bool once = 1;


    if (animation_ability_2.getElapsedTime().asSeconds() >= abilityb2 and once)
    {
        boss.state = Boss2State::Ability_22;
        if (animation_ability_2.getElapsedTime().asSeconds() >= 0.25 * 16 + abilityb2)
        {
            once = false;
            animation_ability_2.restart();
        }
    }
    else if (animation_ability_1.getElapsedTime().asSeconds() >= shooting_ability and !ability_2)
    {
        boss.state = Boss2State::Ability_12;
        if (animation_ability_1.getElapsedTime().asSeconds() >= 0.1258 * 6 + shooting_ability)
            animation_ability_1.restart();
    }
    else if (!ability_1 and distanceToMain <= distance_to_hit and !ability_2)
    {
        boss.state = Boss2State::hitting2;
    }
    else if (distanceToMain <= distance_to_hit)
    {
        boss.state = Boss2State::Standing2;
    }
    else
    {
        if (!hitting and !ability_1 and !ability_2)
        {
            boss.state = Boss2State::Moving2;
        }
    }

    sf::Vector2f direction = character.wizard.getPosition() - boss.shape.getPosition();

    if (direction.x < 0)
    {
        boss.shape.setScale(-10.f, 10.f);
        boss.shape.setOrigin(w_boss / 2.f, 0);
    }
    else
    {
        boss.shape.setScale(10.f, 10.f);
        boss.shape.setOrigin(w_boss / 2.f, 0);
    }


    switch (boss.state)
    {
    case Boss2State::Standing2:
        boss.shape.setTexture(&boss.standingTexture);
        break;
    case Boss2State::Moving2:
        boss.shape.setTexture(&boss.movingTexture);
        break;
    case Boss2State::hitting2:
        boss.shape.setTexture(&boss.shootingTexture);
        hitting = 1;
        break;
    case Boss2State::Ability_12:
        boss.shape.setTexture(&boss.ability_1Texture);
        ability_1 = 1;
        break;
    case Boss2State::Ability_22:
        boss.shape.setTexture(&boss.ability_2Texture);
        ability_2 = 1;
        break;
    }


    if (boss.state == Boss2State::Ability_22)
    {
        static sf::Clock fireB;

        if (fireB.getElapsedTime().asSeconds() >= 0.1)
        {
            boss.currentFrame += 1;

            if (boss.currentFrame >= 2)
            {
                boss.currentFrame = 0;
            }
            boss.shape.setTextureRect(sf::IntRect((int)boss.currentFrame * w_boss, 0, w_boss, h_boss));
            fireB.restart();
        }
    }
    else if (boss.state == Boss2State::Ability_12)
    {
        static sf::Clock fireB;

        if (fireB.getElapsedTime().asSeconds() >= 0.2)
        {
            boss.currentFrame += 1;

            if (boss.currentFrame >= 6)
            {
                boss.currentFrame = 0;
            }
            boss.shape.setTextureRect(sf::IntRect((int)boss.currentFrame * w_boss, 0, w_boss, h_boss));
            fireB.restart();
        }
    }
    else if (boss.state == Boss2State::hitting2)
    {
        static sf::Clock fireB;

        if (fireB.getElapsedTime().asSeconds() >= 0.25)
        {
            boss.currentFrame += 1;

            if (boss.currentFrame >= 4)
            {
                boss.currentFrame = 0;
            }
            boss.shape.setTextureRect(sf::IntRect((int)boss.currentFrame * w_boss, 0, w_boss, h_boss));
            fireB.restart();
        }
    }
    else
    {
        static sf::Clock fireB;

        if (fireB.getElapsedTime().asSeconds() >= 0.2)
        {
            boss.currentFrame += 1;

            if (boss.currentFrame >= 3)
            {
                boss.currentFrame = 0;
            }
            boss.shape.setTextureRect(sf::IntRect((int)boss.currentFrame * w_boss, 0, w_boss, h_boss));
            fireB.restart();
        }
    }

}
void animateability_1(Ability& fireball, Boss2& boss)
{
    static sf::Clock fireB;

    if (fireB.getElapsedTime().asSeconds() >= 0.2)
    {
        fireball.currentFrame += 1;

        if (fireball.currentFrame >= 8)
        {
            fireball.currentFrame = 4;
        }
        fireball.shape.setTextureRect(sf::IntRect((int)fireball.currentFrame * 42, 0, 42, 34));
        fireB.restart();
    }
}
void animateability_2(Abilityb2& poison, status& character)
{
    static sf::Clock fireB;

    if (fireB.getElapsedTime().asSeconds() >= 0.25)
    {
        poison.currentFrame += 1;

        if (poison.currentFrame >= 16)
        {
            poison.currentFrame = 0;
        }
        poison.shape.setTextureRect(sf::IntRect((int)poison.currentFrame * 48, 0, 48, 64));
        fireB.restart();
    }
}

void updateability_1(Ability& fireball, status& character, float deltaTime)
{
    if (fireball.active)
    {
        fireball.shape.move(fireball.velocity * deltaTime);

        if (fireball.shape.getGlobalBounds().intersects(character.wizard.getGlobalBounds()))
        {
            character.hp -= 200;
            fireball.active = false;
        }
    }
}
void updateability_2(Abilityb2& poison, status& character)
{
    if (poison.active)
    {
        static sf::Clock activation;
        if (activation.getElapsedTime().asSeconds() >= 0.25 * 16)
        {
            activation.restart();
            poison.active = false;
        }
    }
}
void moveBoss2(Boss2& boss, status& character, float deltaTime)
{
    if (boss.state != BossState::Ability_1 and boss.state != BossState::Ability_2)
    {
        sf::Vector2f direction = character.wizard.getPosition() - boss.shape.getPosition();
        float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
        sf::Vector2f normalizedDirection = direction / length;

        boss.velocity = normalizedDirection * boss_speed * deltaTime * ch_speed;

        if (length <= distance_to_hit)
        {
            boss.velocity = sf::Vector2f(0.f, 0.f);
        }

        boss.velocity.y += 0 * deltaTime;

        boss.shape.move(boss.velocity);
    }

    if (boss.shape.getPosition().y + boss.shape.getSize().y > Window_height - floorHeight)
    {
        boss.shape.setPosition(boss.shape.getPosition().x, Window_height - floorHeight - boss.shape.getSize().y);
        boss.velocity.y = 0;
    }

    //if (boss.shape.getPosition().x < 0)
    //{
    //    boss.shape.setPosition(0, boss.shape.getPosition().y);
    //}
   /* if (boss.shape.getPosition().x + boss.shape.getSize().x > Window_width)
    {
        boss.shape.setPosition(Window_width - boss.shape.getSize().x, boss.shape.getPosition().y);
    }*/
}
void fireability_1(Ability& fireball, Boss2& boss, status& character)
{
    if (fireball.cooldownTimer.getElapsedTime().asSeconds() >= shooting_ability and boss.currentFrame == 2 and boss.state == Boss2State::Ability_12)
    {
        setupability_1(fireball);
        fireball.cooldownTimer.restart();

        sf::Vector2f direction = character.wizard.getPosition() - boss.shape.getPosition();
        sf::Vector2f normalizedDirection;
        fireball.shape.setPosition(boss.shape.getPosition().x, boss.shape.getPosition().y);

        if (direction.x < 0)
        {
            normalizedDirection = { -1.0f, 0.0f };
            fireball.shape.setScale(-2.f, 2.f);
            fireball.shape.setOrigin(w_boss / 2.5f, 0);
        }
        else
        {
            normalizedDirection = { 1.0f, 0.0f };
            fireball.shape.setScale(2.f, 2.f);
            fireball.shape.setOrigin(w_boss / 2.5f, 0);
        }
        fireball.velocity.x = normalizedDirection.x * bullet_speed;
        fireball.velocity.y = normalizedDirection.y * bullet_speed;

        fireball.active = true;
    }
}
void ability_2(Abilityb2& poison, Boss2& boss, status& character)
{
    if (poison.cooldownTimer.getElapsedTime().asSeconds() >= abilityb2 and boss.state == Boss2State::Ability_22)
    {
        setupability_2(poison);
        poison.cooldownTimer.restart();
        poison.position = character.wizard.getPosition();
        poison.active = true;
    }
}

void bossHit(Boss2& boss, status& character)
{
    float distanceToMain = sqrt(pow(character.wizard.getPosition().x - boss.shape.getPosition().x, 2) +
        pow(character.wizard.getPosition().y - boss.shape.getPosition().y, 2));

    if (distanceToMain <= distance_to_hit)
    {
        boss.state = Boss2State::hitting2;
        if (boss.currentFrame == 3)
        {
            character.hp -= 50;
        }
    }
}




//items 
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
}items[2];

// NPC structure
struct npcs {
    RectangleShape enemy;
    float enemy_max_hp = 100;
    float health = enemy_max_hp;
    bool istimewarpon = false;
    float damage_done = 50;
} enemy;



struct enemies {
    Sprite enemy;
    Texture enemy_tx_ide;
    Texture enemy_tx_run_right;
    Texture enemy_tx_run_left;
    Texture enemy_tx_attack;
    Texture enemy_tx_attack_lift;
    int hp = 100;
    int damage = 25;
    int max_hp = 100;
    float delay = 0.25;
    float timer = 0;
    int i = 0;
    bool ide = true;
    bool attack = false;
    bool run = false;
    bool looking_right;
    enemies() {
        enemy.setPosition(Vector2f(550, 770)); // Initialize Y position to 770
    }
};
vector<enemies> enemies_list;
//struct status {
//    Sprite wizard;
//    int hp = 100;
//    // Add other wizard properties if needed
//};
void load_tx(enemies& enemy) {
    enemy.enemy_tx_ide.loadFromFile("C:\\Users\\Seif2\\source\\repos\\ConsoleApplication8\\ConsoleApplication8\\assets\\spritesheet (1).png");
    /* enemy.enemy_tx_attack.loadFromFile("C:\\Users\\Seif2\\source\\repos\\ConsoleApplication8\\ConsoleApplication8\\assets\\spritesheet (3).png");*/
    enemy.enemy_tx_run_left.loadFromFile("C:\\Users\\Seif2\\source\\repos\\ConsoleApplication8\\ConsoleApplication8\\assets\\spritesheet (2)(1)(1).png");
    enemy.enemy_tx_run_right.loadFromFile("C:\\Users\\Seif2\\source\\repos\\ConsoleApplication8\\ConsoleApplication8\\assets\\spritesheet (2).png");
    enemy.enemy_tx_attack.loadFromFile("C:\\Users\\Seif2\\source\\repos\\ConsoleApplication8\\ConsoleApplication8\\assets\\spritesheet (3).png");
    enemy.enemy_tx_attack_lift.loadFromFile("C:\\Users\\Seif2\\source\\repos\\ConsoleApplication8\\ConsoleApplication8\\assets\\spritesheet (3)(1)(1).png");
}

void ide_animation(enemies& enemy, float dt) {

    enemy.enemy.setScale(2.f, 2.f);
    enemy.enemy.setTexture(enemy.enemy_tx_ide);
    if (enemy.timer < 0) {
        enemy.i++;
        if (enemy.i >= 8) {
            enemy.ide = false;
            enemy.i = 0;
        }
        enemy.enemy.setTextureRect(IntRect((enemy.i * 50), 0, 50, 60));
        enemy.timer = enemy.delay;
    }
    else {
        enemy.timer -= dt;
    }

}

void run_animation(enemies& enemy, status& wizard, float dt) {

    enemy.enemy.setScale(2.f, 2.f);
    if (wizard.wizard.getPosition().x > enemy.enemy.getPosition().x) {

        enemy.enemy.setTexture(enemy.enemy_tx_run_right);
        int num = 55;
        if (enemy.timer < 0) {
            enemy.i++;
            if (enemy.i >= 8) {
                enemy.ide = false;
                enemy.i = 0;
                num = 55;
            }
            if (enemy.i > 4) {
                num = 56;
            }
            enemy.enemy.setTextureRect(IntRect((enemy.i * num), 0, 55, 60));
            enemy.timer = enemy.delay;
        }
        else {
            enemy.timer -= dt;
        }


    }
    else {

        enemy.enemy.setTexture(enemy.enemy_tx_run_left);
        int num = 55;
        if (enemy.timer < 0) {
            enemy.i--;
            if (enemy.i <= 0) {
                enemy.ide = false;
                enemy.i = 7;
                num = 55;
            }
            if (enemy.i < 4) {
                num = 55;
            }
            enemy.enemy.setTextureRect(IntRect((enemy.i * num), 0, 55, 60));
            enemy.timer = enemy.delay;
        }
        else {
            enemy.timer -= dt;
        }

    }


}

void attack_animation(enemies& enemy, status& wizard, float dt) {
    enemy.enemy.setScale(1.5f, 1.5f);

    if (wizard.wizard.getPosition().x > enemy.enemy.getPosition().x) {

        enemy.enemy.setTexture(enemy.enemy_tx_attack);
        int num = 130;
        if (enemy.timer < 0) {
            enemy.i--;
            if (enemy.i <= 0) {
                enemy.ide = false;
                enemy.i = 4;
                num = 130;
                enemy.attack = false;
            }
            if (enemy.enemy.getGlobalBounds().intersects(wizard.wizard.getGlobalBounds())) {
                //wizard.hp -= enemy.damage; // Handle wizard damage
            }
            enemy.enemy.setTextureRect(IntRect((enemy.i * num), 0, 130, 90));
            enemy.timer = enemy.delay;
        }
        else {
            enemy.timer -= dt;
        }

    }
    else {

        enemy.enemy.setTexture(enemy.enemy_tx_attack_lift);
        int num = 130;
        if (enemy.timer < 0) {
            enemy.i++;
            if (enemy.i >= 5) {
                enemy.ide = false;
                enemy.i = 0;
                num = 130;
                enemy.attack = false;
            }
            if (enemy.i > 4) {
                num = 130;
                if (enemy.enemy.getGlobalBounds().intersects(wizard.wizard.getGlobalBounds())) {
                    //wizard.hp -= enemy.damage; // Handle wizard damage
                }
            }
            enemy.enemy.setTextureRect(IntRect((enemy.i * num), 0, 130, 90));
            enemy.timer = enemy.delay;
        }
        else {
            enemy.timer -= dt;
        }

    }

}

void setup_enemy(status& wizard, enemies& enemy, Clock& damageClock, float dt) {
    float wiz_pos = wizard.wizard.getPosition().x;
    float enemy_pos = enemy.enemy.getPosition().x;
    float distance = abs(wiz_pos - enemy_pos);

    if (distance <= 300 && distance >= 30) {
        /*check_animation(enemy);*/
        enemy.run = true;
        enemy.ide = false;
        enemy.attack = false;
        run_animation(enemy, wizard, dt);
        int direction = wiz_pos - enemy_pos;
        float movementSpeed = 0.1f * (direction / abs(direction)); // Normalize direction
        enemy.enemy.move(movementSpeed, 0);
    }
    else if (distance <= 30) {
        /*check_animation(enemy);*/
        enemy.run = false;
        enemy.ide = false;
        //enemy.attack = false;
        attack_animation(enemy, wizard, dt);
        if (damageClock.getElapsedTime().asSeconds() >= 1.5f && abs(wizard.wizard.getPosition().y - enemy.enemy.getPosition().y) < 50) {
            enemy.attack = true;
            damageClock.restart();
            wizard.hp -= enemy.damage; // Apply damage
        }
    }
    else {
        /*check_animation(enemy);*/
        enemy.attack = false;
        enemy.run = false;
        enemy.ide = true;
        ide_animation(enemy, dt);
    }
}

void update_enemies(status& wizard, std::vector<enemies>& enemies_list, Clock& damageClock, float dt)
{
    for (auto it = enemies_list.begin(); it != enemies_list.end(); ) {
        setup_enemy(wizard, *it, damageClock, dt);
        if (it->hp <= 0) {
            wizard.enemy_death_counter++;
            wizard.enemy_death_counter_for_show++;
            if (wizard.enemy_death_counter % wizard.the_divisor == 0)
            {
                wizard.level++;
                wizard.the_divisor += 2;
                /* enemy.enemy_max_hp += 50;*/

                wizard.if_levelup = true;
                wizard.enemy_death_counter = 0;
            }
            it->max_hp += 50;
            it->hp = it->max_hp;
            it = enemies_list.erase(it);
        }
        else {
            ++it;
        }
    }
}








struct maap
{
    Sprite blocks0[5];
    Sprite background_sprite;
    //#include <SFML/Graphics.hpp>
    //#include <SFML/System.hpp>
    //#include <SFML/Window.hpp>
    //#include <SFML/Network.p>hp
    Texture background;
    Sprite ground_sprite;
    Texture ground_Texture;
    //Sprite blocksgetGlobalBounds()_sprite;
    //Texture blocksgetGlobalBounds()_Texture;
    //Sprite blocks[100];
    Sprite blocks2[100];
    Sprite blockTriangle_sprite;
    Texture blockTriangle_Texture;
    Sprite blocks3[100];
    Sprite blockSmall_sprite;
    Texture blockSmall_Texture;
    Sprite blocks4[100];
    Sprite blocksBig_sprite;
    Texture blocksBig_Texture;
    Sprite blocks5[100];
    Sprite blocksFire_sprite;
    Texture blocksFire_Texture;
    Sprite blocks6[100];
    Sprite blocksTriangleLeft_sprite;
    Texture blocksTriangleLeft_Texture;
    Sprite blocks7[100];
    Sprite blocksTriangleRight_sprite;
    Texture blocksTriangleRight_Texture;


};
struct maap2
{
    Sprite blocks0[5];
    Sprite background_sprite;
    //#include <SFML/Graphics.hpp>
    //#include <SFML/System.hpp>
    //#include <SFML/Window.hpp>
    //#include <SFML/Network.p>hp
    Texture background;
    Sprite ground_sprite;
    Texture ground_Texture;
    //Sprite blocksgetGlobalBounds()_sprite;
    //Texture blocksgetGlobalBounds()_Texture;
    //Sprite blocks[100];
    Sprite blocks2[100];
    Sprite blockTriangle_sprite;
    Texture blockTriangle_Texture;
    Sprite blocks3[100];
    Sprite blockSmall_sprite;
    Texture blockSmall_Texture;
    Sprite blocks4[100];
    Texture spikes;
    Sprite Spikes;
    Texture fake_block;
    Sprite Fake_block;
    Sprite blocksBig_sprite;
    Texture blocksBig_Texture;
    Sprite blocks5[100];
    Sprite blocksFire_sprite;
    Texture blocksFire_Texture;
    Sprite blocks6[100];
    Sprite blocksTriangleLeft_sprite;
    Texture blocksTriangleLeft_Texture;
    Sprite blocks7[100];
    Sprite blocksTriangleRight_sprite;
    Texture blocksTriangleRight_Texture;
    Sprite block8[20];
    Sprite block_tree;
    Texture block_Tree;

};


void block_rect(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed);//block3
void block_triangle(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed);//block2
void block_small(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed);//block3
void block_big(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed);//block4
void block_fire(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed);//block5
void block_triangle_left(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed);//block6
void block_triangle_right(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed);//block7
void block0(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed);
void block_tree(maap2& map2);

void Game_play(RenderWindow& window, maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed) {
    if (!level1_completed && level2_completed && level3_completed)
    {
        map.background.loadFromFile("./assets/map background.png");

        //map.background.setSmooth(true);

        map.background_sprite.setTexture(map.background);

        map.ground_Texture.loadFromFile("./assets/Sprite-000111.png");


        map.ground_sprite.setTexture(map.ground_Texture);


        // blocksgetGlobalBounds()_Texture.loadFromFile("E:\\Enas\\Project\\SFML\\ASSETS\\blockgetGlobalBounds().png");
        map.blockTriangle_Texture.loadFromFile("./assets/Sprite-0005.png");
        map.blockSmall_Texture.loadFromFile("./assets/Sprite-0004.png");
        map.blocksBig_Texture.loadFromFile("./assets/Sprite-0002.png");

        //block_getGlobalBounds() (blocks);
       // for (int i = 0; i < 20; i++) {
       /*     if (i == 7) {
                blocks[i].setTexture(ground_Texture);
            }
            else {

                blocks[i].setTexture(blocksSmall_Texture);
            }
        }*/

        block_triangle(map, map2, level1_completed, level2_completed, level3_completed);
        for (int i = 0; i < 100; i++) {

            map.blocks2[i].setTexture(map.blockTriangle_Texture);
        }

        block_small(map, map2, level1_completed, level2_completed, level3_completed);
        for (int i = 0; i < 100; i++) {

            if (i == 100) {
                map.blocks3[i].setTexture(map.ground_Texture);
            }
            else {
                map.blocks3[i].setTexture(map.blockSmall_Texture);
            }

            block_big(map, map2, level1_completed, level2_completed, level3_completed);
            for (int i = 0; i < 100; i++) {
                map.blocks4[i].setTexture(map.blocksBig_Texture);
            }

            block_fire(map, map2, level1_completed, level2_completed, level3_completed);
            for (int i = 0; i < 100; i++) {
                map.blocks5[i].setTexture(map.blocksFire_Texture);
            }

            block_triangle_left(map, map2, level1_completed, level2_completed, level3_completed);
            for (int i = 0; i < 100; i++) {
                map.blocks6[i].setTexture(map.blocksTriangleLeft_Texture);
            }

            block_triangle_right(map, map2, level1_completed, level2_completed, level3_completed);
            for (int i = 0; i < 100; i++) {
                map.blocks7[i].setTexture(map.blocksTriangleRight_Texture);
            }

            block0(map, map2, level1_completed, level2_completed, level3_completed);
        }
    }
    else if (level1_completed && !level2_completed && level3_completed)
    {
        map2.background.loadFromFile("./assets/map2 bg.png");

        //map2.background.setSmooth(true);

        map2.background_sprite.setTexture(map2.background);

        map2.ground_Texture.loadFromFile("./assets/Sprite-0008.png");


        map2.ground_sprite.setTexture(map2.ground_Texture);


        // blocksgetGlobalBounds()_Texture.loadFromFile("E:\\Enas\\Project\\SFML\\ASSETS\\blockgetGlobalBounds().png");
        map2.blockTriangle_Texture.loadFromFile("./assets/Sprite-00015.png");
        map2.blockSmall_Texture.loadFromFile("./assets/Sprite-009.png");
        map2.blocksBig_Texture.loadFromFile("./assets/Sprite-0002.png");
        map2.fake_block.loadFromFile("./assets/Sprite-0010.png");
        map2.blocksTriangleLeft_Texture.loadFromFile("./assets/Sprite-0011.png");
        map2.blocksTriangleRight_Texture.loadFromFile("./assets/Sprite-0014.png");
        map2.spikes.loadFromFile("./assets/Sprite-00016.png");
        map2.block_Tree.loadFromFile("./assets/Sprite-0013.png");
        //block_getGlobalBounds() (blocks);
       // for (int i = 0; i < 20; i++) {
       /*     if (i == 7) {
                blocks[i].setTexture(ground_Texture);
            }
            else {

                blocks[i].setTexture(blocksSmall_Texture);
            }
        }*/

        block_triangle(map, map2, level1_completed, level2_completed, level3_completed);
        for (int i = 0; i < 100; i++) {

            map2.blocks2[i].setTexture(map2.blockTriangle_Texture);
        }

        block_small(map, map2, level1_completed, level2_completed, level3_completed);
        for (int i = 0; i < 100; i++) {

            if (i == 100) {
                map2.blocks3[i].setTexture(map2.ground_Texture);
            }
            else {
                map2.blocks3[i].setTexture(map2.blockSmall_Texture);
            }

            block_big(map, map2, level1_completed, level2_completed, level3_completed);
            for (int i = 0; i < 100; i++) {
                map2.blocks4[i].setTexture(map2.spikes);
            }

            block_fire(map, map2, level1_completed, level2_completed, level3_completed);
            for (int i = 0; i < 100; i++) {
                map2.blocks5[i].setTexture(map2.fake_block);
            }

            block_triangle_left(map, map2, level1_completed, level2_completed, level3_completed);
            for (int i = 0; i < 100; i++) {
                map2.blocks6[i].setTexture(map2.blocksTriangleLeft_Texture);
            }

            block_triangle_right(map, map2, level1_completed, level2_completed, level3_completed);
            for (int i = 0; i < 100; i++) {
                map2.blocks7[i].setTexture(map2.blocksTriangleRight_Texture);

            }
            block_tree(map2);
            for (int i = 0; i < 20; i++) {
                map2.block8[i].setTexture(map2.block_Tree);
            }

            block0(map, map2, level1_completed, level2_completed, level3_completed);
        }
    }

}


// Bullet structure
struct Bullet {
    Sprite bullet;
    Texture bullet_tx;
    Vector2f bullet_velocity;
    float speed;
    float range;

    // Default constructor
    Bullet() : speed(0.0f), range(0.0f) {
        // Initialize other members here if needed
    }

    // Parameterized constructor
    Bullet(Vector2f position, Vector2f direction, float speed = 0.25f, float range = 350.f)
        : speed(speed), range(range) {
        // Initialize other members here if needed
        bullet.setPosition(position);
        bullet_velocity = direction * speed;
    }
};

//statues calculation
void statues_calc(status& wizard) {
    if (wizard.level > wizard.current_level)
    {
        wizard.autodamage = (wizard.autodamage) * (100 + wizard.abilitypower) / 100;
        wizard.fire_damage = (wizard.fire_damage) * (100 + wizard.abilitypower) / 100;
        wizard.heal_health = (wizard.heal_health) * (100 + wizard.abilitypower) / 100;
        wizard.heal_cooldown = (wizard.heal_cooldown) * (static_cast<float>(100) / 100 + wizard.abilityhaste);
        wizard.flash_cooldown = (wizard.flash_cooldown) * (static_cast<float>(100) / 100 + wizard.abilityhaste);
        wizard.fire_cooldown = (wizard.fire_cooldown) * (static_cast<float>(100) / 100 + wizard.abilityhaste);
        wizard.time_warp_cooldown = (wizard.time_warp_cooldown) * (static_cast<float>(100) / 100 + wizard.abilityhaste);
    }
}

void wizard_level(npcs& enemy, status& wizard, bool& ishit, Sprite& hp_button, Sprite& mana_button, Sprite& ap_button, Sprite& attack_speed_button, Sprite& haste_button, Sprite& movement_button, int& counter, Clock& t, RenderWindow& window) {
    Vector2i mousepos = (Mouse::getPosition(window));
    if (enemy.health == 0 && ishit && !wizard.if_levelup)
    {
        wizard.enemy_death_counter++;
        wizard.enemy_death_counter_for_show++;
        if (wizard.enemy_death_counter % wizard.the_divisor == 0)
        {
            wizard.level++;
            wizard.the_divisor += 2;
            enemy.enemy_max_hp += 50;
            wizard.if_levelup = true;
            wizard.enemy_death_counter = 0;
        }
    }
}
// Function to handle movement of the main character
void handle_movement(status& wizard, maap& map, float& velocity_y, bool& can_jump, bool& is_on_ground, float deltatime, float gravity, Clock& it, ani& animation, Sound& jumpsound) {

    //const float gravity = 100.0f;

    // Movement variables
    Vector2f movement(0, 0);

    // Check if the main character is on the ground
    for (int i = 0; i <= 5; i++) {

        if (wizard.wizard.getGlobalBounds().intersects(map.blocks0[i].getGlobalBounds())) {

            if (i == 1 || i == 2 || i == 3 || i == 4) {
                if (wizard.wizard.getPosition().y >= map.blocks0[i].getPosition().y - 45) {

                    wizard.wizard.setPosition(wizard.wizard.getPosition().x, map.blocks0[i].getPosition().y - 45);
                    is_on_ground = true;
                }

            }
        }
    }
    if (is_on_ground) {
        can_jump = true;
        velocity_y = 0; // Reset vertical velocity when on the ground
    }
    else {
        can_jump = false;
    }

    // Handle movement left and right
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        animation.moving = true;
        if (animation.moving)
        {
            animation.lr = false;
            animation.u = 3;
            moving(animation, deltatime, wizard);
            movement.x = -wizard.movementspeed * deltatime;
            it.restart();
        }

    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        animation.moving = true;
        if (animation.moving)
        {
            animation.lr = true;
            animation.u = 4;
            moving(animation, deltatime, wizard);
            movement.x = wizard.movementspeed * deltatime;
            it.restart();
        }
    }

    // Handle jumping
    if (Keyboard::isKeyPressed(Keyboard::Space) && can_jump) {
        velocity_y = -sqrt(2 * gravity * 0.270f * 0.005f); // Apply jump velocity
        can_jump = false;
        sound.jumpSound.play();
    }

    // Update character position based on movement and gravity
    wizard.wizard.move(movement.x, velocity_y);

    // Apply gravity
    velocity_y += gravity * deltatime * 0.005f;

    if (it.getElapsedTime().asSeconds() >= 1.0) {
        if (animation.lr == true) {
            animation.u = 2;
            idle(animation, deltatime, wizard, can_jump);
        }

        else if (animation.lr == false)
        {

            animation.u = 14;
            idle(animation, deltatime, wizard, can_jump);

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

void bullet_animation(float& timer, Bullet& bullet, int& i, int& u, float& delay, float deltatime) {
    if (timer < 0)
    {
        i++;
        if (i < 4)
        {
            i = i % 5;
            bullet.bullet.setTextureRect(IntRect(i * 192, u * 192, 192, 192));
            timer = delay;
        }
        else
        {
            u++;
            u = u % 4;
            i = 0;
        }

        if (i > 4 && u > 3)
        {
            i = 0;
            u = 0;
        }
    }
    else
    {
        timer -= deltatime;
    }
}
void setup_bullets_w(Bullet& bullet) {
    bullet.bullet_tx.loadFromFile("./assets/image.png");
    bullet.bullet.setTexture(bullet.bullet_tx);
    bullet.bullet.setScale(0.28f, .28f);
    bullet.bullet.setTextureRect(IntRect(0, 0, 192, 192));
}
// Function to handle shooting bullets
void shoot_bullet(Vector2f player_position, Vector2f mouse_position, Bullet*& bullets, int& numBullets, Clock& cooldown_clock, float cooldown_duration) {
    if (cooldown_clock.getElapsedTime().asSeconds() > cooldown_duration) {
        Vector2f direction = mouse_position - player_position;
        direction /= sqrt(direction.x * direction.x + direction.y * direction.y); // Normalize the direction vector

        // Allocate memory for one more bullet
        Bullet* temp = new Bullet[numBullets + 1];

        // Copy existing bullets to the new array
        for (int i = 0; i < numBullets; ++i) {
            temp[i] = bullets[i];
        }

        // Create a new bullet at the player's position with the calculated direction
        Bullet new_bullet(player_position, direction);
        setup_bullets_w(new_bullet);
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

        //animation
        animation.aq = true;

        // Add the new bullet to the array
        temp[numBullets] = new_bullet;

        // Deallocate old memory
        delete[] bullets;

        // Update bullets pointer to point to the new array
        bullets = temp;

        // Increment bullet count
        numBullets++;

        // Reset the cooldown clock
        cooldown_clock.restart();

        sound.bulletSound.play();

    }
}

void update_bullets(Bullet*& bullets, int& numBullets, Vector2f& player_center, Boss& boss, std::vector<enemies>& enemies_list) {
    for (int i = 0; i < numBullets; ) {
        bullets[i].bullet.move(bullets[i].bullet_velocity);
        float distance = sqrt(pow(bullets[i].bullet.getPosition().x - player_center.x, 2) +
            pow(bullets[i].bullet.getPosition().y - player_center.y, 2));

        // Check if the bullet exceeds its range or hits the enemy
        bool is_hit = bullets[i].bullet.getGlobalBounds().intersects(boss.shape.getGlobalBounds());


        bool ishit_enemy = false;
        for (auto& enemy : enemies_list) {
            if (bullets[i].bullet.getGlobalBounds().intersects(enemy.enemy.getGlobalBounds())) {
                enemy.hp -= wizard.autodamage; // Decrease enemy health by 10
                ishit_enemy = true;
                break;
            }
        }

        // Remove bullet if it exceeds range or hits the enemy
        if (distance > bullets[i].range || is_hit || ishit_enemy) {
            if (is_hit) {

                if (items[0].extra_damage_active)
                {
                    items[0].extra_damege = 0.05f * wizard.autodamage;
                }
                boss.Health -= wizard.autodamage + items[0].extra_damege;
                //ispoison = true;
                wizard.ishit = true;
            }

            // Shift elements to remove bullet
            for (int j = i; j < numBullets - 1; ++j) {
                bullets[j] = bullets[j + 1];
            }
            // Decrement bullet count
            numBullets--;
            //bullets.erase(bullets.begin() + i);
        }
        else {
            i++;
        }
        // Calculate distance traveled
        // Check if the bullet exceeds its range or hits the enemy
        // Remove bullet if it exceeds range or hits the enemy
        // Shift elements to remove 
    }  // Decrement bullet count
}

void draw_bullets(RenderWindow& window, Bullet* bullets, int numBullets) {
    for (int i = 0; i < numBullets; ++i) {
        window.draw(bullets[i].bullet);
    }
}

// Main character and ground initialization function
void main_character_and_ground() {
    // Initialize the main character (wizard)
    wizard.wizard.setPosition(Vector2f(8000, 440));

    // Initialize the enemy (enemy)
    enemy.enemy.setSize(Vector2f(30, 50));
    enemy.enemy.setFillColor(Color::Magenta);
    enemy.enemy.setOutlineColor(Color::White);
    enemy.enemy.setOutlineThickness(1.5f);
    enemy.enemy.setPosition(Vector2f(400, 440));

    // Initialize the ground (map2)
    /*map2.ground.setSize(Vector2f(2000, 40));
    map2.ground.setFillColor(Color::Red);
    map2.ground.setPosition(Vector2f(0, 800));*/
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
void activate_time_warp(status& wizard, bool& istimewarpon, int& counter, int& rtime) {
    counter++;
    if (counter == 1 || wizard.time_warp_timer.getElapsedTime().asSeconds() > wizard.time_warp_cooldown) {
        // Activate the ability and reset the timer
        wizard.timerR = true;
        rtime = wizard.time_warp_cooldown;
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
void handle_time_warp(status& wizard, npcs& enemy, float deltatime, bool& istimewarpon, int& counter, int& animation_counter, Boss& boss, bool& boss_moving) {

    if (wizard.time_warp_active) {
        if (animation_counter == 0)
        {
            animation.ar = true;
            sound.ability1.play();
        }
        if (wizard.time_warp_timer.getElapsedTime().asSeconds() > 4.f)
        {
            wizard.back_ability = true;
        }
        animation_counter++;
        // Slow down the enemy's movement speed
        enemy.enemy.move(0, 0); // Stop all movements for enemies
        boss_moving = false;
        // Reduce the enemy's movement speed by the slowdown factor
        Vector2f enemy_velocity(0.f, 0.f);
        boss.shape.move(enemy_velocity);
        // Move the enemy using the adjusted velocity
        enemy.enemy.move(enemy_velocity);

        // Check if the ability duration has ended
        if (wizard.time_warp_timer.getElapsedTime().asSeconds() > wizard.time_warp_duration) {
            // Deactivate the ability
            wizard.time_warp_active = false;
            counter = 0;
            animation_counter = 0;
            istimewarpon = false;
            wizard.back_ability = false;
            boss_moving = true;
        }
    }
}


void handle_movement_enemy(npcs& enemy, maap& map, float& velocity_y, bool& is_on_ground, float deltatime, float gravity, bool& istimewarbon) {

    //const float gravity = 100.0f;

    // Movement variables
    Vector2f movement(0, 0);

    // Check if the main character is on the ground
    is_on_ground = enemy.enemy.getGlobalBounds().intersects(map.ground_sprite.getGlobalBounds());
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


void flash_ability(status& wizard, int& counter, int& ftime) {
    // Check if the flash cooldown has elapsed
    counter++;
    if (counter == 1 || wizard.flash_timer.getElapsedTime().asSeconds() > wizard.flash_cooldown) {
        // Calculate the flash direction based on the wizard's facing direction
        // You can define the facing direction as the movement direction (left or right)
        wizard.timerf = true;
        ftime = wizard.flash_cooldown;
        float flash_direction = Keyboard::isKeyPressed(Keyboard::D) ? 1.0f : -1.0f;

        // Calculate the new position after flashing
        Vector2f new_position = wizard.wizard.getPosition() + Vector2f(flash_direction * wizard.flash_distance, 0);

        // Move the wizard to the new position
        wizard.wizard.setPosition(new_position);

        // Reset the flash timer
        wizard.flash_timer.restart();

        sound.ability3.play();
    }
}

void activate_fire_ability(status& wizard, npcs& enemy, Clock& firetime, int& counter, bool is_on_ground, int& counter_of_mana, int& counterrr, int& qtime, int& i, float& timer, float& delay, float deltaTime, Sprite& ui, Sprite& ui2, Sprite& ui3, Sprite& ui4, Sprite& ui5, Sprite& ui6, Boss& boss, bool& firrrrrrre) {
    // Check if the fire ability is available based on its cooldown
    /*if (wizard.fire_timer.getElapsedTime().asSeconds() > wizard.fire_cooldown) {
        // Activate the fire ability
        wizard.fire_active = true;
        wizard.fire_timer.restart();
    }*/
    wizard.fire_active = true;

    // If the fire ability is active
    if (wizard.fire_active)
    {
        if (counterrr == 0 || wizard.fire_timer.getElapsedTime().asSeconds() > wizard.fire_cooldown)
        {
            firrrrrrre = true;
            if (firrrrrrre)
            {
                ui.setPosition(wizard.wizard.getPosition().x + 90, 840);
                ui2.setPosition(wizard.wizard.getPosition().x + 260, 840);
                ui3.setPosition(wizard.wizard.getPosition().x + 430, 840);
                ui4.setPosition(wizard.wizard.getPosition().x - 150, 840);
                ui5.setPosition(wizard.wizard.getPosition().x - 310, 840);
                ui6.setPosition(wizard.wizard.getPosition().x - 470, 840);
            }
            if (counter_of_mana == 0)
            {
                wizard.mana -= 50;
                sound.ability4.play();
            }
            if (timer < 0)
            {
                i++;
                if (i < 5)
                {
                    i = i % 6;
                    ui.setTextureRect(IntRect(i * 32, 0, 32, 12));
                    ui2.setTextureRect(IntRect(i * 32, 0, 32, 12));
                    ui3.setTextureRect(IntRect(i * 32, 0, 32, 12));
                    ui4.setTextureRect(IntRect(i * 32, 0, 32, 12));
                    ui5.setTextureRect(IntRect(i * 32, 0, 32, 12));
                    ui6.setTextureRect(IntRect(i * 32, 0, 32, 12));
                    timer = delay;

                }
                else
                {
                    i = 0;
                }
            }
            else {
                timer -= deltaTime;
            }

            wizard.timerq = true;
            qtime = wizard.fire_cooldown;
            counter_of_mana++;
            if (counter_of_mana == 1)
            {
                animation.ae = true;
            }
            if (firetime.getElapsedTime().asSeconds() > 0.5 && counter < 4)
            {
                counter++;
                if (ui.getGlobalBounds().intersects(enemy.enemy.getGlobalBounds()))
                {
                    enemy.health -= wizard.fire_damage;
                }
                else if (ui.getGlobalBounds().intersects(boss.shape.getGlobalBounds()))
                {
                    boss.Health -= wizard.fire_damage;
                }
                for (auto& enemy : enemies_list) {
                    if (ui.getGlobalBounds().intersects(enemy.enemy.getGlobalBounds())) {
                        enemy.hp -= wizard.fire_damage; // Decrease enemy health by 10
                        /*ishit_enemy = true;*/
                        break;
                    }
                }

                if (counter == 4)
                {
                    wizard.fire_active = false;
                    firrrrrrre = false;
                    counter = 0;
                    wizard.isfire = false;
                    counter_of_mana = 0;
                    animation.ae = false;
                    counterrr++;
                    wizard.fire_timer.restart();
                }
                firetime.restart();
            }
        }
    }
    //sound.ability2.play();
}

void wizard_power_up(Vector2f mouse_position, Sprite& hp_button, Sprite& mana_button, Sprite& ap_button, Sprite& attack_speed_button, Sprite& haste_button, Sprite& movement_button, status& wizard) {
    if (wizard.if_levelup)
    {


        if (hp_button.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            hp_button.setScale(1.3f, 1.3f);
            //sound.hover_sound.play();
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                wizard.max_hp += 100;
                wizard.hp = wizard.max_hp;
                wizard.mana = wizard.max_mana;
                wizard.current_level = wizard.level;
                wizard.ishit = false;
                wizard.if_levelup = false;
            }
        }
        else
        {
            hp_button.setScale(1.1f, 1.1f);
        }
        if (mana_button.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            mana_button.setScale(1.3f, 1.3f);
            //sound.hover_sound.play();
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                wizard.max_mana += 50;
                wizard.hp = wizard.max_hp;
                wizard.mana = wizard.max_mana;
                wizard.current_level = wizard.level;
                wizard.ishit = false;
                wizard.if_levelup = false;
            }
        }
        else
        {
            mana_button.setScale(1.1f, 1.1f);
        }
        if (ap_button.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            ap_button.setScale(1.3f, 1.3f);
            //sound.hover_sound.play();
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                wizard.abilitypower += 10;
                statues_calc(wizard);
                wizard.hp = wizard.max_hp;
                wizard.mana = wizard.max_mana;
                wizard.current_level = wizard.level;
                wizard.ishit = false;
                wizard.if_levelup = false;
                //counter = 0;
            }
        }
        else
        {
            ap_button.setScale(1.1f, 1.1f);
        }
        if (attack_speed_button.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            attack_speed_button.setScale(1.3f, 1.3f);
            //sound.hover_sound.play();
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                wizard.auto_cooldown_duration -= 0.05;
                wizard.hp = wizard.max_hp;
                wizard.mana = wizard.max_mana;
                wizard.current_level = wizard.level;
                wizard.ishit = false;
                wizard.if_levelup = false;
            }
        }
        else
        {
            attack_speed_button.setScale(1.1f, 1.1f);
        }
        if (haste_button.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            haste_button.setScale(1.3f, 1.3f);
            //sound.hover_sound.play();
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                wizard.abilityhaste += 5;
                statues_calc(wizard);
                wizard.hp = wizard.max_hp;
                wizard.mana = wizard.max_mana;
                wizard.current_level = wizard.level;
                wizard.ishit = false;
                wizard.if_levelup = false;
            }
        }
        else
        {
            haste_button.setScale(1.1f, 1.1f);
        }
        if (movement_button.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
        {
            movement_button.setScale(1.3f, 1.3f);
            //sound.hover_sound.play();
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                wizard.movementspeed += 25;
                wizard.hp = wizard.max_hp;
                wizard.mana = wizard.max_mana;
                wizard.current_level = wizard.level;
                wizard.ishit = false;
                wizard.if_levelup = false;
            }
        }
        else
        {
            movement_button.setScale(1.1f, 1.1f);
        }

    }
}

void heal_ability(status& wizard, int& counter, int& wtime, int& mana_counter) {
    counter++;
    if (counter == 1 || wizard.heal.getElapsedTime().asSeconds() > wizard.heal_cooldown)
    {
        if (wizard.heal.getElapsedTime().asSeconds() > wizard.heal_cooldown)
        {
            mana_counter = 0;
        }
        mana_counter++;
        if (mana_counter == 1)
        {
            wizard.mana -= 75;
            sound.ability2.play();
        }
        wizard.timerw = true;
        wtime = wizard.heal_cooldown;
        animation.aw = true;
        wizard.heal.restart();
        wizard.hp += wizard.heal_health;
        if (wizard.hp > wizard.max_hp)
        {
            wizard.hp = wizard.max_hp;
        }
    }
}

float non_negative(float& num) {
    if (num < 0)
    {
        num = 0;
        return num;
    }
    else
    {
        return num;
    }
}

void boss_fight(status& wizard, bool& wiz_in_area) {
    if (wiz_in_area)
    {
        if (wizard.wizard.getPosition().x < 8400)
        {
            wizard.wizard.setPosition(0, wizard.wizard.getPosition().y);
        }
        if (wizard.wizard.getPosition().x + 96 > 10300)
        {
            wizard.wizard.setPosition(10300 - 96, wizard.wizard.getPosition().y);
        }
    }
}

void the_boss1_is_dead(Boss& boss, bool& wiz_in_area, bool& level1_completed, bool& level2_completed, bool& level3_completed) {
    if (boss.Health == 0)
    {
        wiz_in_area = false;
        level1_completed = true;
        level2_completed = false;
        level3_completed = true;
        //the changes that will hapen in level 2
    }
}

void portal() {

}

//dfine:=========================
struct UI
{
    Texture Ui;
    Texture depuffs;
    Sprite UI;
    Sprite Depuff;
    Texture pause;
    Sprite pause_icon;
    Texture holderbar;
    Sprite holder;
    Texture border;
    Sprite border_w;
    Sprite border_r;
    Sprite border_q;
    Sprite border_f;
    Sprite border_i1;
    Sprite border_i2;
    Texture between;
    Sprite bet;

    Texture flame;
    Sprite flame_icon;
    Texture people_compressed;
    Sprite people_app2;
    Texture thunder;
    Sprite thunder_icon;
    Texture button_r;
    Sprite r;
    Texture button_w;
    Sprite w;
    Texture button_q;
    Sprite q;
    Texture button_f;
    Sprite f;
    Texture timer;
    Sprite timer_f;
    Sprite timer_r;
    Sprite timer_w;
    Sprite timer_q;
    Texture portal_state;
    Sprite portal;
    Texture volcano_state;
    Sprite volcano;
    Texture cards_holder;
    Sprite c_holder;
    Texture cards;
    Sprite card1;
    Sprite card2;
    Sprite card3;
    Sprite card4;
    Texture hp;
    Texture mn;

    Texture ability_2_back;
    Sprite back;

    Texture Status;
    Texture DoneBTN;
    Sprite StatusSp;
    Sprite DoneBTN_SP;

    Sprite Hpbar;
    Sprite Manabar;

    Texture heal_tx;
    Sprite heal;

    Texture xp, xpbtx;
    Sprite xpbar, xpb;

    Texture pause_sheet;
    Sprite pause_holder;

    Texture quittx, resumetx;
    Sprite quit, resume;

    Texture ab1_tx;
    Sprite ab1, ab12, ab13, ab14, ab15, ab16;

    Font font;
    Text timerq, timerR, timerf, timerw, enemy_death_counter, text;

    Texture plus_button;
    Sprite hp_button, mana_button, ap_button, movement_button, attack_speed_button, haste_button;

    string enemy_deaths;


    int qtime = 0;
    int wtime = 0;
    int ftime = 0;
    int rtime = 0;
};



//Functions:=====================

void PDrawUI(UI& ui) {
    ui.Ui.loadFromFile("./assets/UI.png");
    ui.UI.setTexture(ui.Ui);
    ui.UI.setPosition(15, 10);
    ui.UI.setScale(0.85, 0.85);

    ui.pause.loadFromFile("./assets/Pause.png");
    ui.pause_icon.setTexture(ui.pause);
    ui.pause_icon.setPosition(1820, 20);
    ui.pause_icon.setScale(1.3, 1.3);

    ui.holderbar.loadFromFile("./assets/1.png");
    ui.holder.setTexture(ui.holderbar);
    ui.holder.setPosition(1920 / 2 - 320, 860);
    ui.holder.setScale(1.35, 1.35);

    ui.border.loadFromFile("./assets/Pxiel_Art_UI_borders3.png");
    ui.border_f.setTexture(ui.border);
    ui.border_q.setTexture(ui.border);
    ui.border_w.setTexture(ui.border);

    ui.border_r.setTexture(ui.border);
    ui.border_r.setScale(0.9, 0.9);

    ui.border_w.setPosition(1920 / 2 - 220, 902);
    ui.border_w.setScale(0.9, 0.9);


    ui.border_q.setPosition(1920 / 2 + 20, 902);
    ui.border_q.setScale(0.9, 0.9);


    ui.border_f.setPosition(1920 / 2 + 270, 902);
    ui.border_f.setScale(0.9, 0.9);

    ui.flame.loadFromFile("./assets/flame.png");
    ui.flame_icon.setTexture(ui.flame);
    ui.flame_icon.setPosition(760, 921);
    ui.flame_icon.setScale(0.125, 0.125);

    ui.people_compressed.loadFromFile("./assets/time_warp.png");
    ui.people_app2.setTexture(ui.people_compressed);
    ui.people_app2.setPosition(1005, 925);
    ui.people_app2.setScale(0.95, 0.95);

    ui.thunder.loadFromFile("./assets/Flash_HD.png");
    ui.thunder_icon.setTexture(ui.thunder);
    ui.thunder_icon.setPosition(1920 / 2 + 294, 923);
    ui.thunder_icon.setScale(0.25, 0.25);

    ui.heal_tx.loadFromFile("./assets/heal.png");
    ui.heal.setTexture(ui.heal_tx);
    ui.heal.setScale(0.42, 0.42);


    ui.button_f.loadFromFile("./assets/F.png");
    ui.f.setTexture(ui.button_f);
    ui.f.setPosition(1920 / 2 + 245, 940);
    ui.f.setScale(1.3, 1.3);

    ui.button_q.loadFromFile(". / assets / Q.png");
    ui.q.setTexture(ui.button_q);
    ui.q.setPosition(1920 / 2 - 247, 940);
    ui.q.setScale(1.3, 1.3);

    ui.button_w.loadFromFile("./assets/W.png");
    ui.w.setTexture(ui.button_w);
    ui.w.setPosition(1920 / 2, 940);
    ui.w.setScale(1.3, 1.3);

    ui.button_r.loadFromFile("./assets/R.png");
    ui.r.setTexture(ui.button_r);
    ui.r.setScale(1.3, 1.3);

    ui.timer.loadFromFile("./assets/Rectangle_1.png");
    ui.timer_q.setTexture(ui.timer);
    ui.timer_q.setPosition(758, 918);
    ui.timer_q.setScale(0.93, 0.93);

    ui.timer_w.setTexture(ui.timer);
    ui.timer_w.setScale(0.93, 0.93);

    ui.timer_r.setTexture(ui.timer);
    ui.timer_r.setPosition(998, 918);
    ui.timer_r.setScale(0.93, 0.93);

    ui.timer_f.setTexture(ui.timer);
    ui.timer_f.setPosition(1248, 918);
    ui.timer_f.setScale(0.93, 0.93);

    ui.portal_state.loadFromFile("./assets/8-deadlands_portal.png");
    ui.portal.setTexture(ui.portal_state);
    ui.portal.setPosition(36, 36);
    ui.portal.setScale(0.35, 0.35);

    ui.volcano_state.loadFromFile("./assets/1-deadlands_vulcano.png");
    ui.volcano.setTexture(ui.volcano_state);
    ui.volcano.setPosition(36, 36);
    ui.volcano.setScale(0.35, 0.35);

    ui.cards_holder.loadFromFile("./assets/fantasy empty playboard.png");
    ui.c_holder.setTexture(ui.cards_holder);
    ui.c_holder.setPosition(480, 220);
    ui.c_holder.setScale(0.55, 0.55);

    ui.cards.loadFromFile(". / assets / card fantasy golden.png");
    ui.card1.setTexture(ui.cards);
    ui.card1.setPosition(520, 280);
    ui.card1.setScale(0.4, 0.4);

    ui.card2.setTexture(ui.cards);
    ui.card2.setPosition(870, 280);
    ui.card2.setScale(0.4, 0.4);

    ui.card3.setTexture(ui.cards);
    ui.card3.setPosition(1200, 280);
    ui.card3.setScale(0.4, 0.4);

    ui.hp.loadFromFile("./assets/healthBar.png");
    ui.Hpbar.setTexture(ui.hp);
    ui.Hpbar.setPosition(15, 10);
    ui.Hpbar.setScale(0.85, 0.85);

    ui.mn.loadFromFile("./assets/manaBar.png");
    ui.Manabar.setTexture(ui.mn);
    ui.Manabar.setPosition(15, 10);
    ui.Manabar.setScale(0.85, 0.85);

    ui.xp.loadFromFile("./assets/Xp_bar.png");
    ui.xpbar.setTexture(ui.xp);
    ui.xpbar.setPosition(15, 10);
    ui.xpbar.setScale(0.85, 0.85);

    ui.xpbtx.loadFromFile("./assets/XPBarFill.png");
    ui.xpb.setTexture(ui.xpbtx);
    ui.xpb.setScale(0.85, 0.85);
    ui.xpb.setPosition(365, 92);

    ui.Status.loadFromFile("./assets/status.png");
    ui.DoneBTN.loadFromFile("./assets/button.png");
    ui.StatusSp.setTexture(ui.Status);
    ui.DoneBTN_SP.setTexture(ui.DoneBTN);
    ui.Status.setSmooth(true);
    ui.DoneBTN.setSmooth(true);
    ui.StatusSp.setPosition(Vector2f(720, 130));
    ui.StatusSp.setScale(1.5, 1.5);
    ui.DoneBTN_SP.setPosition(Vector2f(950, 650));
    ui.DoneBTN_SP.setScale(1.5, 1.5);

    ui.plus_button.loadFromFile("./assets/PlusButton.png");
    ui.hp_button.setTexture(ui.plus_button);
    ui.hp_button.setPosition(1172, 394);
    ui.hp_button.setScale(1.1f, 1.1f);
    ui.mana_button.setTexture(ui.plus_button);
    ui.mana_button.setPosition(1172, 434);
    ui.mana_button.setScale(1.1f, 1.1f);
    ui.ap_button.setTexture(ui.plus_button);
    ui.ap_button.setPosition(1172, 476);
    ui.ap_button.setScale(1.1f, 1.1f);
    ui.attack_speed_button.setTexture(ui.plus_button);
    ui.attack_speed_button.setPosition(1172, 600);
    ui.attack_speed_button.setScale(1.1f, 1.1f);
    ui.movement_button.setTexture(ui.plus_button);
    ui.movement_button.setPosition(1172, 516);
    ui.movement_button.setScale(1.1f, 1.1f);
    ui.haste_button.setTexture(ui.plus_button);
    ui.haste_button.setPosition(1172, 560);
    ui.haste_button.setScale(1.1f, 1.1f);

    ui.pause_sheet.loadFromFile("./assets/spritesheet_13.png");
    ui.pause_holder.setTexture(ui.pause_sheet);
    ui.pause_holder.setPosition(-100, 80);
    ui.pause_holder.setScale(2, 2);

    ui.quittx.loadFromFile("./assets/button_Quit.png");
    ui.quit.setTexture(ui.quittx);
    ui.quit.setPosition(Vector2f(895, 650));
    ui.quit.setScale(2.f, 2.f);

    ui.resumetx.loadFromFile("./assets/button_Resume.png");
    ui.resume.setTexture(ui.resumetx);
    ui.resume.setPosition(Vector2f(895, 250));
    ui.resume.setScale(2.f, 2.f);

    ui.font.loadFromFile(". / assets/antiquity - print.ttf");
    ui.timerq.setFont(ui.font);
    ui.timerR.setFont(ui.font);
    ui.timerf.setFont(ui.font);
    ui.timerw.setFont(ui.font);
    ui.enemy_death_counter.setFont(ui.font);
    ui.text.setPosition(Vector2f(20, 180));
    ui.enemy_death_counter.setPosition(Vector2f(480, 180));
    ui.text.setFont(ui.font);

    ui.ability_2_back.loadFromFile("./assets/Space Background.png");
    ui.back.setTexture(ui.ability_2_back);
    ui.back.setScale(2.5, 2.3);

    ui.ab1_tx.loadFromFile("./assets/05.png");
    ui.ab1.setTexture(ui.ab1_tx);
    ui.ab12.setTexture(ui.ab1_tx);
    ui.ab13.setTexture(ui.ab1_tx);
    ui.ab14.setTexture(ui.ab1_tx);
    ui.ab15.setTexture(ui.ab1_tx);
    ui.ab16.setTexture(ui.ab1_tx);
    ui.ab1.setScale(5.f, 5.f);
    ui.ab12.setScale(5.f, 5.f);
    ui.ab13.setScale(5.f, 5.f);
    ui.ab14.setScale(5.f, 5.f);
    ui.ab15.setScale(5.f, 5.f);
    ui.ab16.setScale(5.f, 5.f);
}
void enemy_deaths_counter(UI& ui) {
    ui.enemy_deaths = to_string(wizard.enemy_death_counter_for_show);
    ui.text.setString("Enemies Death Counter :");
    ui.text.Bold;
    ui.text.setOutlineThickness(0.5f);
    ui.enemy_death_counter.setString(ui.enemy_deaths);
    ui.enemy_death_counter.Bold;
    ui.enemy_death_counter.setOutlineThickness(0.5f);
}
void qwf_timer(UI& ui, Clock& qq, Clock& rr, Clock& ff, Clock& ww) {
    if (wizard.timerR && rr.getElapsedTime().asSeconds() > 1.f)
    {
        string rtimme = to_string(ui.rtime);
        ui.timerR.setString(rtimme);
        ui.timerR.setScale(1.5, 1.5);
        ui.timerR.setCharacterSize(42);
        ui.timerR.setOutlineThickness(0.5f);
        ui.timerR.setPosition(Vector2f(1005, 925));
        rr.restart();
        if (ui.rtime == 0)
        {
            wizard.timerR = false;
        }
        ui.rtime--;
    }
    if (wizard.timerq && qq.getElapsedTime().asSeconds() > 1.f)
    {
        string qtimme = to_string(ui.qtime);
        ui.timerq.setString(qtimme);
        ui.timerq.setScale(1.5, 1.5);
        ui.timerq.setCharacterSize(42);
        ui.timerq.setOutlineThickness(0.5f);
        ui.timerq.setPosition(Vector2f(770, 915));
        qq.restart();
        if (ui.qtime == 0)
        {
            wizard.timerq = false;
        }
        ui.qtime--;
    }
    if (wizard.timerf && ff.getElapsedTime().asSeconds() > 1.f)
    {
        string ftimme = to_string(ui.ftime);
        ui.timerf.setString(ftimme);
        ui.timerf.setScale(1.5, 1.5);
        ui.timerf.setCharacterSize(42);
        ui.timerf.setOutlineThickness(0.5f);
        ui.timerf.setPosition(Vector2f(1254, 923));
        ff.restart();
        if (ui.ftime == 0)
        {
            wizard.timerf = false;
        }
        ui.ftime--;
    }
    if (wizard.timerw && ww.getElapsedTime().asSeconds() > 1.f)
    {
        string wtimme = to_string(ui.wtime);
        ui.timerw.setString(wtimme);
        ui.timerw.setScale(1.5, 1.5);
        ui.timerw.setCharacterSize(42);
        ui.timerw.setOutlineThickness(0.5f);
        ww.restart();
        if (ui.wtime == 0)
        {
            wizard.timerw = false;
        }
        ui.wtime--;
    }
}
void PShowStatus() {}
void DepuffSwap() {}
void HealthAnimationSwap(int CurrantHealth, UI& ui) {
    int FrameNum = 1;
    FrameNum = CurrantHealth / 51;
    ui.Hpbar.setTextureRect(IntRect(600 * FrameNum, 0, 600, 160));


}
void ManaAnimationSwap(int Currantmana, UI& ui) {
    int MFrameNum = 1;
    MFrameNum = Currantmana / 50;
    ui.Manabar.setTextureRect(IntRect(600 * MFrameNum, 0, 600, 160));
}

void xp_animation(float i, UI& ui) {
    i = 132 / wizard.the_divisor;
    ui.xpb.setTextureRect(IntRect(0.f, 0.f, wizard.enemy_death_counter * i, 24));
}

void view_position(View& view, RenderWindow& window, maap& map, UI& ui, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed) {
    if (!level1_completed && level2_completed && level3_completed)
    {
        map.background_sprite.setPosition(view.getCenter().x - window.getSize().x / 2, view.getCenter().y - window.getSize().y / 2);
    }
    else if (level1_completed && !level2_completed && level3_completed)
    {
        map2.background_sprite.setPosition(view.getCenter().x - window.getSize().x / 2, view.getCenter().y - window.getSize().y / 2 - 42);
    }
    ui.UI.setPosition(view.getCenter().x - window.getSize().x / 2 + 15, view.getCenter().y - window.getSize().y / 2 + 10);
    ui.pause_icon.setPosition(view.getCenter().x - window.getSize().x / 2 + 1820, view.getCenter().y - window.getSize().y / 2 + 20);
    ui.holder.setPosition(view.getCenter().x - window.getSize().x / 2 + 1920 / 2 - 320, view.getCenter().y - window.getSize().y / 2 + 860);
    ui.flame_icon.setPosition(view.getCenter().x - window.getSize().x / 2 + 715, view.getCenter().y - window.getSize().y / 2 + 921);
    ui.people_app2.setPosition(view.getCenter().x - window.getSize().x / 2 + 1920 / 2 + 25.5, view.getCenter().y - window.getSize().y / 2 + 925);
    ui.thunder_icon.setPosition(view.getCenter().x - window.getSize().x / 2 + 1920 / 2 + 148, view.getCenter().y - window.getSize().y / 2 + 923);
    ui.f.setPosition(view.getCenter().x - window.getSize().x / 2 + 1920 / 2 + 110, view.getCenter().y - window.getSize().y / 2 + 940);
    ui.q.setPosition(view.getCenter().x - window.getSize().x / 2 + 1920 / 2 - 280, view.getCenter().y - window.getSize().y / 2 + 940);
    ui.w.setPosition(view.getCenter().x - window.getSize().x / 2 + 1920 / 2 - 150, view.getCenter().y - window.getSize().y / 2 + 940);
    ui.r.setPosition(view.getCenter().x - window.getSize().x / 2 + 1920 / 2 - 15, view.getCenter().y - window.getSize().y / 2 + 940);
    ui.timer_q.setPosition(view.getCenter().x - window.getSize().x / 2 + 713, view.getCenter().y - window.getSize().y / 2 + 918);
    ui.timer_r.setPosition(view.getCenter().x - window.getSize().x / 2 + 978.5, view.getCenter().y - window.getSize().y / 2 + 918);
    ui.timer_f.setPosition(view.getCenter().x - window.getSize().x / 2 + 1103, view.getCenter().y - window.getSize().y / 2 + 918);
    ui.Hpbar.setPosition(view.getCenter().x - window.getSize().x / 2 + 15, view.getCenter().y - window.getSize().y / 2 + 10);
    ui.Manabar.setPosition(view.getCenter().x - window.getSize().x / 2 + 15, view.getCenter().y - window.getSize().y / 2 + 10);
    ui.xpbar.setPosition(view.getCenter().x - window.getSize().x / 2 + 15, view.getCenter().y - window.getSize().y / 2 + 10);
    ui.xpb.setPosition(view.getCenter().x - window.getSize().x / 2 + 365, view.getCenter().y - window.getSize().y / 2 + 92);
    ui.StatusSp.setPosition(view.getCenter().x - window.getSize().x / 2 + 720, view.getCenter().y - window.getSize().y / 2 + 130);
    ui.DoneBTN_SP.setPosition(view.getCenter().x - window.getSize().x / 2 + 950, view.getCenter().y - window.getSize().y / 2 + 650);
    ui.hp_button.setPosition(view.getCenter().x - window.getSize().x / 2 + 1172, view.getCenter().y - window.getSize().y / 2 + 394);
    ui.mana_button.setPosition(view.getCenter().x - window.getSize().x / 2 + 1172, view.getCenter().y - window.getSize().y / 2 + 434);
    ui.ap_button.setPosition(view.getCenter().x - window.getSize().x / 2 + 1172, view.getCenter().y - window.getSize().y / 2 + 476);
    ui.attack_speed_button.setPosition(view.getCenter().x - window.getSize().x / 2 + 1172, view.getCenter().y - window.getSize().y / 2 + 600);
    ui.movement_button.setPosition(view.getCenter().x - window.getSize().x / 2 + 1172, view.getCenter().y - window.getSize().y / 2 + 516);
    ui.haste_button.setPosition(view.getCenter().x - window.getSize().x / 2 + 1172, view.getCenter().y - window.getSize().y / 2 + 560);
    ui.pause_holder.setPosition(view.getCenter().x - window.getSize().x / 2 - 100, view.getCenter().y - window.getSize().y / 2 + 80);
    ui.quit.setPosition(view.getCenter().x - window.getSize().x / 2 + 895, view.getCenter().y - window.getSize().y / 2 + 650);
    ui.resume.setPosition(view.getCenter().x - window.getSize().x / 2 + 895, view.getCenter().y - window.getSize().y / 2 + 250);
    ui.text.setPosition(view.getCenter().x - window.getSize().x / 2 + 20, view.getCenter().y - window.getSize().y / 2 + 180);
    ui.enemy_death_counter.setPosition(view.getCenter().x - window.getSize().x / 2 + 480, view.getCenter().y - window.getSize().y / 2 + 180);
    ui.border_w.setPosition(view.getCenter().x - window.getSize().x / 2 + 1920 / 2 - 265, view.getCenter().y - window.getSize().y / 2 + 902);
    ui.border_q.setPosition(view.getCenter().x - window.getSize().x / 2 + 1920 / 2 - 135, view.getCenter().y - window.getSize().y / 2 + 902);
    ui.border_f.setPosition(view.getCenter().x - window.getSize().x / 2 + 1920 / 2 + 125, view.getCenter().y - window.getSize().y / 2 + 902);
    ui.border_r.setPosition(view.getCenter().x - window.getSize().x / 2 + 1920 / 2, view.getCenter().y - window.getSize().y / 2 + 902);
    ui.timerR.setPosition(view.getCenter().x - window.getSize().x / 2 + 1920 / 2 + 19.5, view.getCenter().y - window.getSize().y / 2 + 915);
    ui.timerq.setPosition(view.getCenter().x - window.getSize().x / 2 + 720, view.getCenter().y - window.getSize().y / 2 + 915);
    ui.timerf.setPosition(view.getCenter().x - window.getSize().x / 2 + 1120, view.getCenter().y - window.getSize().y / 2 + 915);
    ui.heal.setPosition(view.getCenter().x - window.getSize().x / 2 + 849.5, view.getCenter().y - window.getSize().y / 2 + 924);
    ui.timer_w.setPosition(view.getCenter().x - window.getSize().x / 2 + 843, view.getCenter().y - window.getSize().y / 2 + 918);
    ui.timerw.setPosition(view.getCenter().x - window.getSize().x / 2 + 842, view.getCenter().y - window.getSize().y / 2 + 915);
    ui.back.setPosition(view.getCenter().x - window.getSize().x / 2, view.getCenter().y - window.getSize().y / 2);
}

void blocks_colision(maap& map, bool& is_on_ground, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed) {
    if (!level1_completed && level2_completed && level3_completed)
    {
        for (int i = 0; i < 5; i++) {

            if (i == 1 || i == 3 || i == 4) {
                map.blocks0[i].setTexture(map.ground_Texture);
            }
            else if (i == 2)
                map.blocks0[i].setTexture(map.blocksBig_Texture);
        }

        for (int i = 0; i < 100; i++) {
            FloatRect block3_bounds = map.blocks2[i].getGlobalBounds();
            FloatRect player_bounds = wizard.wizard.getGlobalBounds();
            if (player_bounds.intersects(block3_bounds)) {
                Vector2f correctionVector;

                // Calculate the overlap on each axis
                float xOverlap = std::min(player_bounds.left + player_bounds.width - block3_bounds.left,
                    block3_bounds.left + block3_bounds.width - player_bounds.left);
                float yOverlap = std::min(player_bounds.top + player_bounds.height - block3_bounds.top,
                    block3_bounds.top + block3_bounds.height - player_bounds.top);

                // Move the player away based on the side of collision
                if (xOverlap >= yOverlap) {
                    // Adjust the player's position on the y-axis based on the side of collision
                    if (player_bounds.top < block3_bounds.top) {
                        correctionVector.y = -yOverlap; // Move up
                    }
                    else {
                        correctionVector.y = yOverlap; // Move down
                        wizard.wizard.move(0, 3);
                    }
                }
                else {
                    // Adjust the player's position on the x-axis based on the side of collision
                    if (player_bounds.left < block3_bounds.left) {
                        correctionVector.x = -xOverlap; // Move left

                    }
                    else {
                        correctionVector.x = xOverlap; // Move right
                    }
                }

                is_on_ground = true;
                // Move the player away from the block using the calculated correction vector
                wizard.wizard.move(correctionVector);
            }
        }

        /*for (int i = 0; i <= 5; i++) {

            if (wizard.wizard.getGlobalBounds().intersects(map.blocks0[i].getGlobalBounds())) {

                if (i == 1 || i == 2 || i == 3 || i == 4) {
                    if (wizard.wizard.getPosition().y >= map.blocks0[i].getPosition().y - 45) {

                        wizard.wizard.setPosition(wizard.wizard.getPosition().x, map.blocks0[i].getPosition().y - 45);
                        is_on_ground = true;
                    }

                }
            }
        }*/


        for (int i = 0; i < 100; i++) {
            FloatRect block3_bounds = map.blocks3[i].getGlobalBounds();
            FloatRect player_bounds = wizard.wizard.getGlobalBounds();
            if (player_bounds.intersects(block3_bounds)) {
                Vector2f correctionVector;

                // Calculate the overlap on each axis
                float xOverlap = std::min(player_bounds.left + player_bounds.width - block3_bounds.left,
                    block3_bounds.left + block3_bounds.width - player_bounds.left);
                float yOverlap = std::min(player_bounds.top + player_bounds.height - block3_bounds.top,
                    block3_bounds.top + block3_bounds.height - player_bounds.top);

                // Move the player away based on the side of collision
                if (xOverlap >= yOverlap) {
                    // Adjust the player's position on the y-axis based on the side of collision
                    if (player_bounds.top < block3_bounds.top) {
                        correctionVector.y = -yOverlap; // Move up
                    }
                    else {
                        correctionVector.y = yOverlap; // Move down
                    }
                }
                else {
                    // Adjust the player's position on the x-axis based on the side of collision
                    if (player_bounds.left < block3_bounds.left) {
                        correctionVector.x = -xOverlap; // Move left

                    }
                    else {
                        correctionVector.x = xOverlap; // Move right
                    }
                }
                is_on_ground = true;
                // Move the player away from the block using the calculated correction vector
                wizard.wizard.move(correctionVector);
            }
        }
    }
    else if (level1_completed && !level2_completed && level3_completed)
    {
        for (int i = 0; i < 5; i++) {

            if (i == 0 || i == 1 || i == 2 || i == 3) {
                map2.blocks0[i].setTexture(map2.ground_Texture);
            }
            else if (i == 2)
                map2.blocks0[i].setTexture(map2.blockSmall_Texture);

        }
        for (int i = 0; i < 100; i++) {
            FloatRect block3_bounds = map2.blocks2[i].getGlobalBounds();
            FloatRect player_bounds = wizard.wizard.getGlobalBounds();
            if (player_bounds.intersects(block3_bounds)) {
                Vector2f correctionVector;

                // Calculate the overlap on each axis
                float xOverlap = std::min(player_bounds.left + player_bounds.width - block3_bounds.left,
                    block3_bounds.left + block3_bounds.width - player_bounds.left);
                float yOverlap = std::min(player_bounds.top + player_bounds.height - block3_bounds.top,
                    block3_bounds.top + block3_bounds.height - player_bounds.top);

                // Move the player away based on the side of collision
                if (xOverlap >= yOverlap) {
                    // Adjust the player's position on the y-axis based on the side of collision
                    if (player_bounds.top < block3_bounds.top) {
                        correctionVector.y = -yOverlap; // Move up
                    }
                    else {
                        correctionVector.y = yOverlap; // Move down
                        wizard.wizard.move(0, 3);
                    }
                }
                else {
                    // Adjust the player's position on the x-axis based on the side of collision
                    if (player_bounds.left < block3_bounds.left) {
                        correctionVector.x = -xOverlap; // Move left

                    }
                    else {
                        correctionVector.x = xOverlap; // Move right
                    }
                }
                is_on_ground = true;
                // Move the player away from the block using the calculated correction vector
                wizard.wizard.move(correctionVector);
            }
        }

        for (int i = 0; i <= 4; i++) {

            if (wizard.wizard.getGlobalBounds().intersects(map2.blocks0[i].getGlobalBounds())) {

                if (i == 0 || i == 1 || i == 2 || i == 3) {
                    if (wizard.wizard.getPosition().y >= map2.blocks0[i].getPosition().y - 85) {

                        wizard.wizard.setPosition(wizard.wizard.getPosition().x, map2.blocks0[i].getPosition().y - 85);
                        is_on_ground = true;
                    }

                }




            }


        }






        for (int i = 0; i < 100; i++) {
            FloatRect block3_bounds = map2.blocks3[i].getGlobalBounds();
            FloatRect player_bounds = wizard.wizard.getGlobalBounds();
            if (player_bounds.intersects(block3_bounds)) {
                Vector2f correctionVector;

                // Calculate the overlap on each axis
                float xOverlap = std::min(player_bounds.left + player_bounds.width - block3_bounds.left,
                    block3_bounds.left + block3_bounds.width - player_bounds.left);
                float yOverlap = std::min(player_bounds.top + player_bounds.height - block3_bounds.top,
                    block3_bounds.top + block3_bounds.height - player_bounds.top);

                // Move the player away based on the side of collision
                if (xOverlap >= yOverlap) {
                    // Adjust the player's position on the y-axis based on the side of collision
                    if (player_bounds.top < block3_bounds.top) {
                        correctionVector.y = -yOverlap; // Move up
                    }
                    else {
                        correctionVector.y = yOverlap; // Move down
                    }
                }
                else {
                    // Adjust the player's position on the x-axis based on the side of collision
                    if (player_bounds.left < block3_bounds.left) {
                        correctionVector.x = -xOverlap; // Move left

                    }
                    else {
                        correctionVector.x = xOverlap; // Move right
                    }
                }
                is_on_ground = true;
                // Move the player away from the block using the calculated correction vector
                wizard.wizard.move(correctionVector);
            }
        }
    }

}
bool level1_completed = true;
bool level2_completed = false;
bool level3_completed = true;

int main() {
    RenderWindow window(sf::VideoMode(1920, 1080), "SFML Health Bar");


    Boss boss;
    SetupBoss(boss, wizard);

    Bullllllet bullllet;
    setupBullet(bullllet);

    Bullllllet* bulllets = new Bullllllet[maxBullets];
    int numBulllets = 0;

    Fireball fireball;
    setupFireball(fireball);

    Ability2 ability2;
    setupAbility2(ability2);

    Boss2 boss2;
    SetupBoss2(boss2, wizard);

    Ability ball;
    setupability_1(ball);

    Abilityb2 poison;
    setupability_2(poison);

    maap map;
    maap2 map2;
    UI ui;
    map.background_sprite.setScale(1.55, 1.59);
    map2.background_sprite.setScale(1.79, 1.79);
    View view = window.getDefaultView();

    bool isPaused = false;
    PDrawUI(ui);
    Clock clock;
    float deltaTime = 0;
    int page = 1;

    SOUND(sound);

    IntRect frameRect(0, 0, 768, 385);// Example frame size (adjust as needed)
    ui.pause_holder.setTextureRect(frameRect); // Set the initial frame

    // Animation variables
    int frameCount = 10; // Number of frames in the animation
    int currentFrame = 0; // Index of the current frame
    Clock clock1;
    float frameDuration = 0.1f;

    Clock qq;
    Clock ww;
    Clock ff;
    Clock rr;

    int i = 0;
    bool pause_buttons = false;
    float timer = 0;
    float delay = 0.12f;

    Clock it;

    // Initialize the main character and ground
    main_character_and_ground();
    //set_texture(wizard);
    wizard.wiz_tx.loadFromFile("./texturs/main c/6.png");
    wizard.wizard.setTexture(wizard.wiz_tx);
    wizard.wizard.setTextureRect(IntRect(0, 0, 96, 98));

    //ab1
    int i_ab1 = 0;
    float ab1_delay = 0.1, ab1_timer = 0;
    bool firrrrrrre = false;

    float bullet_timer = 0;
    int i_bullet = 0, u_bullet = 0;
    float bullet_delay = 0.5f;

    Bullet* bullets = nullptr;
    int numBullets = 0;

    // Clock to manage shooting cooldown
    Clock cooldown_clock;

    // Gravity and movement settings
    const float gravity = 100.0f;
    float velocity_y = 0;
    float velocity_y_enemy = 0;
    bool can_jump = false;
    bool is_on_ground = false;
    bool ispoison = false;
    //bool isfire = false;
    bool wiz_in_area = false;
    bool level = false;

    int items_statues_counter = 0;
    int mana_counter = 0;
    int fire_counter = 0;
    int ultimate = 0;
    int flash = 0;
    int bullet_counter = 0;
    int animation_counter = 0;

    // Clock to track game time
    Clock gametime;

    Clock time;

    Clock tfisrt;

    Clock shockWaveClock; // Clock to manage shock wave cooldown

    Clock firetime;

    Clock second_item_passive;

    Clock power_up_t;

    Clock jump_clock;

    bool boss_moving = true;

    int second_item_counter = 0;

    int counter = 1;

    int heal_counter = 0;
    int mana_heal_counter = 0;

    int counter_fire = 0;
    Clock poison_timer;
    float t = 0;
    float deltatime = 0;

    int xp_bar = 0;
    int counter_xp = 0;

    int jump_counter = 0;
    bool new_level = true;

    //---------------------------------------------
    Clock damageClock;

    enemies enemy5;
    load_tx(enemy5);
    int num = 500;
    int i_enemy = 0;

    Clock enemies_C;

    
    //--------------------------------------------



    while (window.isOpen()) {
        sf::Event event;
        clock.restart();
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Pause or unpause the game on 'P' key press
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                isPaused = !isPaused; // Toggle the state
                i = 0;
                sound.pausedSound.play();
            }
            ///////////////////////////////////////////
            if (wizard.wizard.getPosition().x > 400000 && mappp == true && !level1_completed && level2_completed && level3_completed) {

                level1_completed = true;
                level2_completed = false;
                Game_play(window, map, map2, level1_completed, level2_completed, level3_completed);
                //////////////////////
                wizard.wizard.setPosition(10, 500);

                mappp = false;
            }
            if (wizard.wizard.getPosition().x > 60000 && mappp == true && level1_completed && !level2_completed && level3_completed) {

                level1_completed = false;
                level2_completed = true;
                ////////////////////////////////////
                Game_play(window, map, map2, level1_completed, level2_completed, level3_completed);
                mappp = false;
            }
            if (isPaused)
            {
                Vector2i mouse_Position = Mouse::getPosition(window);
                Vector2f mousePosition = window.mapPixelToCoords(mouse_Position);
                if (ui.resume.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    ui.resume.setScale(2.2, 2.2);
                    //sound.hover_sound.play();
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        isPaused = false;
                    }
                }
                else if (ui.quit.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    ui.quit.setScale(2.2, 2.2);
                    //sound.hover_sound.play();
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        window.close();
                    }
                }
                else
                {
                    ui.resume.setScale(2., 2.);
                    ui.quit.setScale(2., 2.);
                }
            }

            if (!isPaused) {

                // Get the mouse position
                Vector2i mouse_Position = Mouse::getPosition(window);
                Vector2f mousePosition = window.mapPixelToCoords(mouse_Position);
                if (Mouse::isButtonPressed(Mouse::Left))//Check if the mouse is pressed
                {
                    // Check if the mouse position is within the bounds of the text
                    if (ui.pause_icon.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        //page = 2;//the page of the kybaords
                        sound.pausedSound.play();
                        i = 0;
                        isPaused = true;
                    }
                }
                //if the mouse is not pressed
                if (ui.pause_icon.getGlobalBounds().contains(mousePosition.x, mousePosition.y))//if the mouse is on the button 
                {
                    //sound.hover_sound.play();
                    ui.pause_icon.setScale(1.2, 1.2);//make the button bigger by scale of 0.1 or as you want
                }
                else
                {
                    //if the mouse if not on the buttton
                    ui.pause_icon.setScale(1, 1);//return the button to his regular size
                }
            }
        }
        HealthAnimationSwap(wizard.hp, ui);
        ManaAnimationSwap(wizard.mana, ui);
        if (!isPaused) {
            non_negative(wizard.hp);
            non_negative(wizard.mana);

            view.setCenter(wizard.wizard.getPosition().x, 540);

            pause_buttons = false;
            if (Keyboard::isKeyPressed(Keyboard::R) && animation.rab.getElapsedTime().asSeconds() > 1) {
                animation.rab.restart();
                activate_time_warp(wizard, enemy.istimewarpon, ultimate, ui.rtime);
            }
            if (Keyboard::isKeyPressed(Keyboard::W) && animation.wab.getElapsedTime().asSeconds() > 1)
            {
                heal_ability(wizard, heal_counter, ui.wtime, mana_heal_counter);
                animation.wab.restart();
            }
            if (animation.aw) {
                if (animation.lr == true) {
                    it.restart();
                    animation.u = 1;
                    abw(animation, deltaTime, wizard);

                }
                else if (animation.lr == false) {
                    it.restart();
                    animation.u = 16;
                    abw(animation, deltaTime, wizard);

                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Q) && animation.qab.getElapsedTime().asSeconds() > 1) {
                animation.qab.restart();
                wizard.isfire = true;
            }
            if (wizard.isfire)
            {
                activate_fire_ability(wizard, enemy, firetime, counter_fire, is_on_ground, mana_counter, fire_counter, ui.qtime, i_ab1, ab1_timer, ab1_delay, deltaTime, ui.ab1, ui.ab12, ui.ab13, ui.ab14, ui.ab15, ui.ab16, boss, firrrrrrre);
                if (animation.ae) {
                    it.restart();
                    animation.u = 6;
                    abe(animation, deltaTime, wizard);
                }
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
            handle_time_warp(wizard, enemy, deltaTime, enemy.istimewarpon, ultimate, animation_counter, boss, boss_moving);
            if (animation.ar) {
                it.restart();
                animation.u = 7;
                abr(animation, deltaTime, wizard);

            }

            if (Keyboard::isKeyPressed(Keyboard::F)) {
                flash_ability(wizard, flash, ui.ftime);
            }

            Vector2f player_center;
            player_center.x = wizard.wizard.getPosition().x + 65;
            player_center.y = wizard.wizard.getPosition().y + 19;
            window.setView(view);
            Vector2i mousePosition = Mouse::getPosition(window);
            Vector2f mouse_position = window.mapPixelToCoords(mousePosition);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                shoot_bullet(player_center, mouse_position, bullets, numBullets, cooldown_clock, wizard.auto_cooldown_duration);
            }
            if (animation.aq)
            {
                if (animation.lr == true) {
                    it.restart();
                    animation.u = 5;
                    ab(animation, deltaTime, wizard);

                }
                else if (animation.lr == false) {

                    it.restart();
                    animation.u = 15;
                    ab(animation, deltaTime, wizard);
                }
            }
            // Update bullets' positions and manage them
            update_bullets(bullets, numBullets, player_center, boss, enemies_list);
            qwf_timer(ui, qq, ww, ff, rr);
            xp_animation(xp_bar, ui);
            wizard_level(enemy, wizard, wizard.ishit, ui.hp_button, ui.mana_button, ui.ap_button, ui.attack_speed_button, ui.haste_button, ui.movement_button, counter_xp, power_up_t, window);
            wizard_power_up(mouse_position, ui.hp_button, ui.mana_button, ui.ap_button, ui.attack_speed_button, ui.haste_button, ui.movement_button, wizard);
            //poison effect
            //poison(ispoison, time, counter);
            enemy_deaths_counter(ui);
            if (!level1_completed && level2_completed && level3_completed)
            {
                ///----------------------------------------
                if (enemies_C.getElapsedTime().asSeconds() > 20)
                {
                    if (wizard.enemy_death_counter < 5)
                    {
                        for (int i = i_enemy; i < 5 + i_enemy; i++) {
                            enemy5.enemy.setPosition(num, 770);
                            enemies_list.push_back(enemy5);
                            num += 200;
                        }
                        i_enemy += 5;
                    }
                    enemies_C.restart();
                }

                update_enemies(wizard, enemies_list, damageClock, deltaTime);
                ///-------------------------------------------
                if (new_level)
                {
                    Game_play(window, map, map2, level1_completed, level2_completed, level3_completed);
                }
                new_level = false;
                blocks_colision(map, is_on_ground, map2, level1_completed, level2_completed, level3_completed);
                view_position(view, window, map, ui, map2, level1_completed, level2_completed, level3_completed);
                // Handle movement
                handle_movement(wizard, map, velocity_y, can_jump, is_on_ground, deltaTime, gravity, it, animation, sound.jumpSound);
                if (can_jump == false)
                {
                    jump_counter++;
                    if (jump_counter == 1)
                    {
                        jump_clock.restart();
                    }
                    if (animation.lr == true) {
                        animation.u = 12;
                        jump_animation(animation, deltatime, wizard, jump_clock, is_on_ground, jump_counter);
                    }
                    else if (animation.lr == false)
                    {

                        animation.u = 11;
                        jump_animation(animation, deltatime, wizard, jump_clock, is_on_ground, jump_counter);

                    }
                }

                handle_movement_enemy(enemy, map, velocity_y_enemy, is_on_ground, deltaTime, gravity, enemy.istimewarpon);

                animateBoss(boss, wizard, deltaTime);
                moveBoss(boss, wizard, deltaTime, boss_moving, wizard.wizard, wiz_in_area);
                fireBullet(bulllets, numBulllets, boss, wizard, deltaTime, boss.currentFrame);
                fireBigFireball(fireball, boss, wizard);
                activateAbility2(ability2, boss, wizard);
                updateFireball(fireball, wizard, deltaTime);
                updateAbility2(ability2, wizard, deltaTime);
                get_damaged(animation, deltaTime, wizard);
                //cout << wizard.hp << endl;
                //boss_fight(wizard, wiz_in_area);

                //9127.25\805
                if (wizard.hp == 0)
                {
                    animation.u = 13;
                    animation.death = true;
                    death_ani(animation, deltaTime, wizard);

                }
            }
            else if (level1_completed && !level2_completed && level3_completed)
            {
                //changes in level 2
                if (new_level)
                {
                    Game_play(window, map, map2, level1_completed, level2_completed, level3_completed);
                }
                new_level = false;
                blocks_colision(map, is_on_ground, map2, level1_completed, level2_completed, level3_completed);
                view_position(view, window, map, ui, map2, level1_completed, level2_completed, level3_completed);
                // Handle movement
                handle_movement(wizard, map, velocity_y, can_jump, is_on_ground, deltaTime, gravity, it, animation, sound.jumpSound);
                if (can_jump == false)
                {
                    jump_counter++;
                    if (jump_counter == 1)
                    {
                        jump_clock.restart();
                    }
                    if (animation.lr == true) {
                        animation.u = 12;
                        jump_animation(animation, deltatime, wizard, jump_clock, is_on_ground, jump_counter);
                    }
                    else if (animation.lr == false)
                    {

                        animation.u = 11;
                        jump_animation(animation, deltatime, wizard, jump_clock, is_on_ground, jump_counter);

                    }
                }

                animateBoss2(boss2, wizard, deltaTime);
                moveBoss2(boss2, wizard, deltaTime);

                bossHit(boss2, wizard);
                fireability_1(ball, boss2, wizard);
                updateability_1(ball, wizard, deltaTime);
                ability_2(poison, boss2, wizard);
                updateability_2(poison, wizard);




                get_damaged(animation, deltaTime, wizard);
                //cout << wizard.hp << endl;
                //boss_fight(wizard, wiz_in_area);

                //9127.25\805
                if (wizard.hp == 0)
                {
                    animation.u = 13;
                    animation.death = true;
                    death_ani(animation, deltaTime, wizard);

                }
            }
            else if (level1_completed && level2_completed && !level3_completed)
            {
                //cahnges in level 3
            }
        }
        if (isPaused)
        {
            if (timer < 0)
            {
                i++;
                if (i < 9)
                {
                    i = i % 10;
                    ui.pause_holder.setTextureRect(IntRect(i * 768, 0, 768, 385));
                    timer = delay;

                }
                else
                {
                    ui.pause_holder.setTextureRect(IntRect(9 * 768, 0, 768, 385));
                    pause_buttons = true;
                }
            }
            else {
                timer -= deltaTime;
            }
        }

        //sf::Time elapsed = clock.restart();
        window.clear();
        if (!level1_completed && level2_completed && level3_completed)
        {
            window.draw(map.background_sprite);
        }
        else if (level1_completed && !level2_completed && level3_completed)
        {
            window.draw(map2.background_sprite);
        }


        if (wizard.back_ability)
        {
            window.draw(ui.back);
        }
        window.setView(view);
        if (!level1_completed && level2_completed && level3_completed)
        {
            for (int i = 0; i < 17; i++) {
                window.draw(map.blocks2[i]);  //blocks triangle
            }
            for (int i = 0; i < 17; i++) {
                window.draw(map.blocks3[i]);
            }
            for (int i = 0; i < 5; i++) {
                window.draw(map.blocks0[i]);  //blocks small
            }//blocks small
            for (size_t i = 0; i < numBullets; i++)
            {
                bullet_animation(bullet_timer, bullets[i], i_bullet, u_bullet, bullet_delay, deltaTime);
                bullets[i].bullet.setTexture(bullets[i].bullet_tx);
                window.draw(bullets[i].bullet);
            }
            window.draw(boss.shape);

            for (size_t i = 0; i < numBulllets; i++)
            {
                animateBullet(bulllets[i]);
                bulllets[i].shape.setTexture(bulllets[i].bulletTexture);
                window.draw(bulllets[i].shape);
            }

            if (ability2.active = 1)
            {
                animateAbility2(ability2);
                updateAbility2(ability2, wizard, deltaTime);
                ability2.shape.setTexture(ability2.AbilityTexture);
                window.draw(ability2.shape);

            }

            if (fireball.active)
            {
                animateFireBall(fireball, boss);
                fireball.shape.setTexture(fireball.AbilityTexture);
                window.draw(fireball.shape);
            }

            for (const auto& enemy : enemies_list) {
                window.draw(enemy.enemy);
            }

        }
        else if (level1_completed && !level2_completed && level3_completed)
        {
            for (int i = 0; i < 4; i++) {
                window.draw(map2.blocks2[i]);  //blocks triangle
            }
            for (int i = 0; i < 18; i++) {
                window.draw(map2.blocks3[i]);

            }
            for (int i = 1; i < 16; i++) {
                window.draw(map2.blocks4[i]);
            }
            for (int i = 0; i < 4; i++) {
                window.draw(map2.blocks5[i]);
            }

            for (int i = 0; i < 4; i++) {
                window.draw(map2.blocks0[i]);

                //blocks small
            }//blocks small
            window.draw(boss2.shape);
            if (ball.active)
            {
                animateability_1(ball, boss2);
                ball.shape.setTexture(ball.AbilityTexture);
                window.draw(ball.shape);
            }

            if (poison.active)
            {
                animateability_2(poison, wizard);
                poison.shape.setTexture(poison.AbilityTexture);
                poison.shape.setPosition(poison.position);
                window.draw(poison.shape);
            }

        }
        // Draw bullets

        //draw_bullets(window, bullets, numBullets);

        // Draw the wizard and enemy
        window.draw(wizard.wizard);
        window.draw(enemy.enemy);
        if (!isPaused)
        {
            if (firrrrrrre)
            {
                window.draw(ui.ab1);
                window.draw(ui.ab12);
                window.draw(ui.ab13);
                window.draw(ui.ab14);
                window.draw(ui.ab15);
                window.draw(ui.ab16);
            }


            window.draw(ui.UI);
            window.draw(ui.pause_icon);
            window.draw(ui.holder);
            window.draw(ui.border_w);
            window.draw(ui.border_q);
            window.draw(ui.border_f);
            window.draw(ui.border_r);
            window.draw(ui.flame_icon);
            window.draw(ui.people_app2);
            window.draw(ui.thunder_icon);
            window.draw(ui.heal);
            window.draw(ui.f);
            window.draw(ui.q);
            window.draw(ui.w);
            window.draw(ui.r);
            //window.draw(portal);
            //window.draw(volcano);
            window.draw(ui.Hpbar);
            window.draw(ui.Manabar);
            window.draw(ui.text);
            window.draw(ui.enemy_death_counter);
            window.draw(ui.xpbar);
            window.draw(ui.xpb);
            //window.draw(timer_w);
            if (wizard.if_levelup)
            {
                window.draw(ui.StatusSp);
                window.draw(ui.ap_button);
                window.draw(ui.hp_button);
                window.draw(ui.mana_button);
                window.draw(ui.movement_button);
                window.draw(ui.attack_speed_button);
                window.draw(ui.haste_button);
            }
            if (wizard.timerq)
            {
                window.draw(ui.timer_q);
                window.draw(ui.timerq);
            }
            if (wizard.timerw)
            {
                window.draw(ui.timer_w);
                window.draw(ui.timerw);
            }
            if (wizard.timerR)
            {
                window.draw(ui.timer_r);
                window.draw(ui.timerR);
            }
            if (wizard.timerf)
            {
                window.draw(ui.timer_f);
                window.draw(ui.timerf);
            }
        }
        else if (isPaused)
        {
            //window.draw(StatusSp);
            //window.draw(DoneBTN_SP);
            window.draw(ui.pause_holder);
            if (pause_buttons)
            {
                window.draw(ui.resume);
                window.draw(ui.quit);
            }
        }
        window.display();
        deltaTime = clock.getElapsedTime().asSeconds();
    }
    delete[] bullets;
    return 0;
}

void idle(ani& animation, float dt, status& wizard, bool can_jump) {
    if ((!wizard.hp == 0))
    {
        if (!animation.damage)
        {
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
    }
}

void ab(ani& animation, float dt, status& wizard) {


    if (animation.timer < 0) {
        animation.i++;
        if (animation.i >= 6) {


            animation.aq = false;
            animation.i = 0;

        }
        wizard.wizard.setTextureRect(IntRect((animation.i * 96), (animation.u * 99), 96, 98));
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
void death_ani(ani& animation, float dt, status& wizard) {
    animation.ae = false;
    animation.aq = false;
    animation.ar = false;
    animation.aw = false;
    animation.moving = false;
    animation.damage = false;
    if (animation.timer < 0) {

        animation.i++;
        if (animation.i < 12) {
            wizard.wizard.setTextureRect(IntRect((animation.i * 96), (animation.u * 99.2), 96, 98));
            animation.timer = animation.delayq;
        }
        else
        {
            wizard.wizard.setTextureRect(IntRect((12 * 96), (animation.u * 99.2), 96, 98));
        }
        /*animation.death = false;
        animation.i = 0;*/
    }
    else {
        animation.timer -= dt;
    }
}
void jump_animation(ani& animation, float dt, status& wizard, Clock& jump_clock, bool on_ground, int& jump_counter) {
    if (animation.timer < 0) {
        animation.i_jump++;
        if (animation.i_jump < 10/*&&jump_clock.getElapsedTime().asSeconds()<1*/) {
            wizard.wizard.setTextureRect(IntRect((animation.i_jump * 96), (animation.u * 99.2), 96, 98));
            animation.timer = animation.delay_jump;
        }
        else
        {
            wizard.wizard.setTextureRect(IntRect((10 * 96), (animation.u * 99.2), 96, 98));
        }
        /*animation.death = false;
        animation.i = 0;*/
        if (on_ground == true)
        {
            jump_counter = 0;
            animation.i_jump = 0;
            jump_clock.restart();
        }
    }
    else {
        animation.timer -= dt;
    }
}

void get_damaged(ani& animation, float dt, status& wizard) {
    if (animation.damage)
    {
        if (animation.timer < 0) {
            animation.i_damge++;

            if (animation.i_damge >= 6) {
                animation.ar = false;
                animation.i_damge = 0;
                animation.damage = false;
            }

            wizard.wizard.setTextureRect(IntRect((animation.i_damge * 96), (animation.u_damage * 98), 96, 98));
            animation.timer = animation.delayq;


        }
        else {
            animation.timer -= dt;
        }
    }
}


void block_small(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed) {

    if (!level1_completed && level2_completed && level3_completed)
    {
        map.blocks3[1].setPosition(1620, 690);
        map.blocks3[1].setScale(1, 1);
        map.blocks3[2].setPosition(1300, 590);
        map.blocks3[2].setScale(1, 1);
        map.blocks3[3].setPosition(1950, 510);
        map.blocks3[3].setScale(1, 1);
        map.blocks3[4].setPosition(1620, 320);
        map.blocks3[4].setScale(1, 1);

        map.blocks3[6].setPosition(2280, 650);
        map.blocks3[6].setScale(1, 1);

        map.blocks3[8].setPosition(4000, 600);
        map.blocks3[8].setScale(1, 1);
        map.blocks3[9].setPosition(4500, 600);
        map.blocks3[9].setScale(1, 1);
        map.blocks3[10].setPosition(4800, 670);
        map.blocks3[10].setScale(1, 1);
        map.blocks3[11].setPosition(4250, 480);
        map.blocks3[11].setScale(1, 1);
        map.blocks3[12].setPosition(5200, 690);
        map.blocks3[12].setScale(1, 1);
        map.blocks3[13].setPosition(5600, 600);
        map.blocks3[13].setScale(1, 1);
        map.blocks3[14].setPosition(6600, 700);
        map.blocks3[14].setScale(1, 1);
        map.blocks3[15].setPosition(6950, 560);
        map.blocks3[15].setScale(1, 1);
        map.blocks3[16].setPosition(7650, 600);
        map.blocks3[16].setScale(1, 1);
    }
    else if (level1_completed && !level2_completed && level3_completed)
    {
        map2.blocks3[1].setPosition(1720, 530);
        map2.blocks3[1].setScale(1, 1);
        map2.blocks3[2].setPosition(1300, 650);
        map2.blocks3[2].setScale(1, 1);
        map2.blocks3[3].setPosition(2150, 510);
        map2.blocks3[3].setScale(1, 1);
        //   map2.blocks3[4].setPosition(1620, 320);
         //  map2.blocks3[4].setScale(1, 1);

          // map2.blocks3[6].setPosition(2280, 650);
           //map2.blocks3[6].setScale(1, 1);

        map2.blocks3[4].setPosition(4000, 670);
        map2.blocks3[4].setScale(1, 1);
        map2.blocks3[5].setPosition(4700, 600);
        map2.blocks3[5].setScale(1, 1);
        //map2.blocks3[10].setPosition(4800, 670);
        //map2.blocks3[10].setScale(1, 1);
        map2.blocks3[6].setPosition(4250, 480);
        map2.blocks3[6].setScale(1, 1);
        map2.blocks3[7].setPosition(5200, 690);
        map2.blocks3[7].setScale(1, 1);
        map2.blocks3[8].setPosition(5600, 600);
        map2.blocks3[8].setScale(1, 1);
        map2.blocks3[9].setPosition(6600, 700);
        map2.blocks3[9].setScale(1, 1);
        map2.blocks3[10].setPosition(7100, 650);
        map2.blocks3[10].setScale(1, 1);
        map2.blocks3[11].setPosition(7500, 540);
        map2.blocks3[11].setScale(1, 1);
        map2.blocks3[12].setScale(1, 1);
        map2.blocks3[12].setPosition(7950, 510);
        map2.blocks3[13].setScale(1, 1);
        map2.blocks3[14].setPosition(8450, 560);
        map2.blocks3[14].setScale(1, 1);
        map2.blocks3[15].setPosition(9000, 790);
        map2.blocks3[15].setScale(1, 1);
    }


}
void block_triangle(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed) {
    if (!level1_completed && level2_completed && level3_completed)
    {
        map.blocks2[0].setPosition(2840, 690);
        map.blocks2[0].setScale(1, 1);
        map.blocks2[1].setPosition(3500, 690);
        map.blocks2[1].setScale(1, 1);
        map.blocks2[2].setPosition(7300, 660);
        map.blocks2[2].setScale(1, 1);

    }
    else if (level1_completed && !level2_completed && level3_completed)
    {
        //map2
        map2.blocks2[0].setPosition(2900, 700);
        map2.blocks2[0].setScale(1, 1);
        map2.blocks2[1].setPosition(3400, 700);
        map2.blocks2[1].setScale(1, 1);
        map2.blocks2[2].setPosition(12300, 710);
        map2.blocks2[2].setScale(1, 1);

    }
}
void block_big(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed) {

    if (!level1_completed && level2_completed && level3_completed)
    {
        map.blocks4[0].setPosition(1400, 640);
        map.blocks4[0].setScale(1, 1);
        map.blocks4[1].setPosition(1100, 500);
        map.blocks4[1].setScale(1, 1);
        map.blocks4[2].setPosition(340, 380);
        map.blocks4[2].setScale(1, 1);
        map.blocks4[3].setPosition(-10, 500);
        map.blocks4[3].setScale(1, 1);
        map.blocks4[4].setPosition(1430, 370);
        map.blocks4[4].setScale(1, 1);
        map.blocks4[5].setPosition(650, 255);
        map.blocks4[5].setScale(1, 1);              //blocks big
        map.blocks4[6].setPosition(510, 780);
        map.blocks4[6].setScale(1, 1);
        map.blocks4[7].setPosition(0, 1040);
        map.blocks4[7].setScale(1, 1);
        map.blocks4[8].setPosition(850, 910);
        map.blocks4[8].setScale(1, 1);
        map.blocks4[9].setPosition(1750, 500);
        map.blocks4[9].setScale(1, 1);
    }
    else if (level1_completed && !level2_completed && level3_completed)
    {
        map2.blocks4[1].setPosition(2650, 880);
        map2.blocks4[1].setScale(1, 1);
        map2.blocks4[2].setPosition(2900, 880);
        map2.blocks4[2].setScale(1, 1);
        map2.blocks4[3].setPosition(3200, 880);
        map2.blocks4[3].setScale(1, 1);
        map2.blocks4[4].setPosition(3480, 880);
        map2.blocks4[4].setScale(1, 1);
        map2.blocks4[5].setPosition(12130, 900);
        map2.blocks4[5].setScale(1.3, 1);
        map2.blocks4[6].setPosition(12550, 900);
        map2.blocks4[6].setScale(1.3, 1);              //blocks big
        map2.blocks4[15].setPosition(6450, 900);
        map2.blocks4[15].setScale(1.3, 1);
        map2.blocks4[7].setPosition(6750, 900);
        map2.blocks4[7].setScale(1.3, 1);
        map2.blocks4[8].setPosition(7100, 900);
        map2.blocks4[8].setScale(1.3, 1);
        map2.blocks4[9].setPosition(7800, 900);
        map2.blocks4[9].setScale(1.3, 1);
        map2.blocks4[10].setPosition(8200, 900);
        map2.blocks4[10].setScale(1.3, 1);
        map2.blocks4[11].setPosition(8600, 900);
        map2.blocks4[11].setScale(1.3, 1);
        map2.blocks4[12].setPosition(9000, 900);
        map2.blocks4[12].setScale(1.3, 1);
        map2.blocks4[13].setPosition(9400, 900);
        map2.blocks4[13].setScale(1.3, 1);
        map2.blocks4[14].setPosition(7450, 900);
        map2.blocks4[14].setScale(1.3, 1);
    }

}
void block_fire(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed) {
    if (!level1_completed && level2_completed && level3_completed)
    {
        map.blocks5[0].setPosition(1400, 640);
        map.blocks5[0].setScale(1, 1);
        map.blocks5[1].setPosition(1100, 500);
        map.blocks5[1].setScale(1, 1);
        map.blocks5[2].setPosition(340, 380);
        map.blocks5[2].setScale(1, 1);
        map.blocks5[3].setPosition(-10, 500);
        map.blocks5[3].setScale(1, 1);
        map.blocks5[4].setPosition(1430, 370);
        map.blocks5[4].setScale(1, 1);
        map.blocks5[5].setPosition(650, 255);
        map.blocks5[5].setScale(1, 1);              //blocks fire
        map.blocks5[6].setPosition(510, 780);
        map.blocks5[6].setScale(1, 1);
        map.blocks5[7].setPosition(0, 1040);
        map.blocks5[7].setScale(1, 1);
        map.blocks5[8].setPosition(850, 910);
        map.blocks5[8].setScale(1, 1);
        map.blocks5[9].setPosition(1750, 500);
        map.blocks5[9].setScale(1, 1);
    }
    else if (level1_completed && !level2_completed && level3_completed)
    {
        map2.blocks5[0].setPosition(12850, 930);
        map2.blocks5[0].setScale(1.5, 1);
        map2.blocks5[1].setPosition(12500, 930);
        map2.blocks5[1].setScale(1.5, 1);
        map2.blocks5[2].setPosition(12330, 930);
        map2.blocks5[2].setScale(1.5, 1);
        map2.blocks5[3].setPosition(12100, 930);
        map2.blocks5[3].setScale(1.5, 1);
        map2.blocks5[1].setPosition(12550, 930);
        map2.blocks5[1].setScale(1.5, 1);
        map2.blocks5[5].setPosition(650, 255);
        map2.blocks5[5].setScale(1, 1);              //blocks fire
        map2.blocks5[6].setPosition(510, 780);
        map2.blocks5[6].setScale(1, 1);
        map2.blocks5[7].setPosition(0, 1040);
        map2.blocks5[7].setScale(1, 1);
        map2.blocks5[8].setPosition(850, 910);
        map2.blocks5[8].setScale(1, 1);
        map2.blocks5[9].setPosition(1750, 500);
        map2.blocks5[9].setScale(1, 1);
    }
}

void block_triangle_left(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed) {
    if (!level1_completed && level2_completed && level3_completed)
    {
        map.blocks6[0].setPosition(1400, 640);
        map.blocks6[0].setScale(1, 1);
        map.blocks6[1].setPosition(1100, 500);
        map.blocks6[1].setScale(1, 1);
        map.blocks6[2].setPosition(340, 380);
        map.blocks6[2].setScale(1, 1);
        map.blocks6[3].setPosition(-10, 500);
        map.blocks6[3].setScale(1, 1);
        map.blocks6[4].setPosition(1430, 370);
        map.blocks6[4].setScale(1, 1);
        map.blocks6[5].setPosition(650, 255);
        map.blocks6[5].setScale(1, 1);              //blocks triangle left
        map.blocks6[6].setPosition(510, 780);
        map.blocks6[6].setScale(1, 1);
        map.blocks6[7].setPosition(0, 1040);
        map.blocks6[7].setScale(1, 1);
        map.blocks6[8].setPosition(850, 910);
        map.blocks6[8].setScale(1, 1);
        map.blocks6[9].setPosition(1750, 500);
        map.blocks6[9].setScale(1, 1);
    }
    else if (level1_completed && !level2_completed && level3_completed)
    {
        map2.blocks6[0].setPosition(500, 430);
        map2.blocks6[0].setScale(.7, .7);
        map2.blocks6[1].setPosition(11100, 430);
        map2.blocks6[1].setScale(.7, .7);
        map2.blocks6[2].setPosition(32240, 380);
        map2.blocks6[2].setScale(1, 1);

    }
}
void block_triangle_right(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed) {
    if (!level1_completed && level2_completed && level3_completed)
    {
        map.blocks7[0].setPosition(1400, 640);
        map.blocks7[0].setScale(1, 1);
        map.blocks7[1].setPosition(1100, 500);
        map.blocks7[1].setScale(1, 1);
        map.blocks7[2].setPosition(340, 380);
        map.blocks7[2].setScale(1, 1);
        map.blocks7[3].setPosition(-10, 500);
        map.blocks7[3].setScale(1, 1);
        map.blocks7[4].setPosition(1430, 370);
        map.blocks7[4].setScale(1, 1);
        map.blocks7[5].setPosition(650, 255);
        map.blocks7[5].setScale(1, 1);              //blocks triangle right
        map.blocks7[6].setPosition(510, 780);
        map.blocks7[6].setScale(1, 1);
        map.blocks7[7].setPosition(0, 1040);
        map.blocks7[7].setScale(1, 1);
        map.blocks7[8].setPosition(850, 910);
        map.blocks7[8].setScale(1, 1);
        map.blocks7[9].setPosition(1750, 600);
        map.blocks7[9].setScale(1, 1);
    }
    else if (level1_completed && !level2_completed && level3_completed)
    {
        map2.blocks7[0].setPosition(10950, 610);
        map2.blocks7[0].setScale(.7, .7);
        map2.blocks7[1].setPosition(13400, 610);
        map2.blocks7[1].setScale(.7, .7);
        map2.blocks7[2].setPosition(340, 380);
        map2.blocks7[2].setScale(1, 1);

    }
}
void block0(maap& map, maap2& map2, bool& level1_completed, bool& level2_completed, bool& level3_completed) {

    if (!level1_completed && level2_completed && level3_completed)
    {
        map.blocks0[1].setPosition(0, 850);//ground 1

        map.blocks0[2].setPosition(3100, 850);//mini ground 1

        map.blocks0[3].setPosition(3800, 850);//ground 2

        map.blocks0[4].setPosition(8000, 850);//ground 3
    }
    else if (level1_completed && !level2_completed && level3_completed)
    {
        map2.blocks0[0].setPosition(0, 930);//ground 1
        map2.blocks0[0].setScale(2.3, 1.5);
        //  map2.blocks0[2].setPosition(3100, 900);//mini ground 1
          //map2.blocks0[2].setScale(2, 2);
        map2.blocks0[1].setPosition(3800, 930);//ground 2
        map2.blocks0[1].setScale(2.3, 1.5);
        map2.blocks0[2].setPosition(9500, 930);//ground 3

        map2.blocks0[2].setScale(2.3, 1.5);
        map2.blocks0[3].setPosition(12800, 930);//ground 3

        map2.blocks0[3].setScale(1.5, 1.5);
    }

}

void block_tree(maap2& map2) {

    map2.block8[0].setPosition(6000, 580);
    map2.block8[0].setScale(1, 1);
    map2.block8[1].setPosition(10100, 580);
    map2.block8[1].setScale(1, 1);
    map2.block8[2].setPosition(13550, 580);
    map2.block8[2].setScale(1, 1);


}