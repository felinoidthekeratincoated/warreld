#include "Action.hh"
#include "Inventory.hh"

// Constructor
Action::Action() {
    sprite.width = Inventory::squareSprite.width;
    sprite.height = Inventory::squareSprite.height;
}

/* Do the action, or use the item or skill. */
void Action::use() {
    // Pass
}