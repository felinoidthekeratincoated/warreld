#ifndef ENTITY_HH
#define ENTITY_HH

#include <string>
#include <fstream>
#include "Movable.hh"
#include "Stat.hh"
#include "json.hpp"
#include "Damage.hh"
#include "Animation.hh"

/* A class for monsters, NPCs, and players to inherit from.
If any features are added later that should reset fall damage, they should
do the resetting of the fall damage in this class or one of its children. */
class Entity : public movable::Movable {

public:
    // To hold information on the stats
    Stat health;
    Stat fullness;
    Stat mana;

    /* Number of ticks of invincibility after taking damage. */
    int invincibilityTime;
    int invincibilityLeft;

    /* Farthest it can fall before taking fall damage (in pixels), 
    -1 for infinity. */
    int maxFallDistance;

    /* Which direction it's facing. */
    bool isFacingRight;

    /* Sitting sprites. */
    std::vector<Sprite> sprites;
    std::vector<Animation> run;

    // Constructor
    Entity(std::string filename, std::string path); 
    Entity();

    // Virtual destructor
    virtual ~Entity();

    virtual void takeDamage(const Damage &damage);

    // Calculate fall damage
    virtual void takeFallDamage();

    /* Do the things! */
    virtual void update();

    /* Render the correct sprite / animation. */
    virtual void render(const Rect &camera);
};

void from_json(const nlohmann::json &j, Entity &entity);

#endif