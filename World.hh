#ifndef WORLD_HH
#define WOLRD_HH

#include <vector>
#include <string>
#include <random> // For the fancy randomness like a normal distribution
#include "Tile.hh"
#include "MapHelpers.hh"

using namespace std;

// Declare some constants
// TODO: fix, this is non-ideal
const TileType DIRT = TileType::DIRT;
const TileType STONE = TileType::STONE;
const TileType EMPTY = TileType::EMPTY;
const TileType PLATFORM = TileType::PLATFORM;
const TileType MAGMA = TileType::MAGMA;
const TileType SANDSTONE = TileType::SANDSTONE;
const TileType MUDSTONE = TileType::MUDSTONE;

// A class for generating a map for a sandbox game
class World {
    // Fields:

    // The array to hold the map info
    // This is a 2d array squished into 1d
    TileType *foreground;
    TileType *background;

    // The height and width of the map, in number of tiles
    int height, width;

    // Default spawn point
    Location spawn;

    // Have a random number generator
    default_random_engine generator;

    // Private methods

    // Really small helper functions that don't directly change tiles

    // Return a pointer to the tile* at x, y
    TileType *findPointer(int x, int y, TileType *array) const;

    // How to make the different types of worlds

    // Generate a world good for testing collision detection
    void generateTest();

    // Generate a tiny world good for testing world generation
    void generateSmolTest();

    // Generate an Earth-type world
    void generateEarth();

    // Parts of generating a world

    // Set all tiles to val
    void setAll(TileType val, TileType *array);

    // Start at top and go down until the type changes
    // Return the height of the first tile of a different type
    // Return -1 if there is no change
    int findChange(int x, int top, TileType *array) const;

    // Merge two arrays, adding them wherever they overlap
    vector<double> merge(int start1, int stop1, 
        const vector<double> &heights1, int start2, int stop2, 
        const vector<double> &heights2) const;

    // Set everything from y1 to y2 to tile
    void setTo(int x, int y1, int y2, TileType tile, TileType *array);

    // Set everything from y1 to y2 to something picked randomly from fill
    void setTo(int x, int y1, int y2, const vector<TileType> &fill, 
        TileType *array);

    // From x = start to x = stop, add heights[x - start] of a randomly 
    // selected Tile* from fill, above the line given by findChange(x, top)
    void addHeights(int start, int stop, const vector<double> &heights, 
        const vector<TileType> &fill, int top, TileType *array);

    // Move the line from findChange(x, top) to heights[x - start]
    void setHeights(int start, int stop, const vector<double> &heights, 
        const vector<TileType> &above, const vector<TileType> &below, int top,
        TileType *array);

    // Linear interpolator
    double lerp(double lo, double hi, double t) const;

    // Generate Perlin noise of length times * wavelength
    vector<double> noise(double range, int times, int wavelength) const;

    // Make an array containing the information for an irregular triangle with
    // width b and height h
    vector<double> makeTriangle(int b, int h, double mean, double stddev);

    /* Make a canyon, and fill it with alternating layers of fill
       This can also be used to make triangles with alternating layers of fill
       x and y are the locations of the middle of the base, width is the width
       at the base, height is distance from the peak to the base (should be
       positive for desert-style pillars or negative for canyons), fill is
       a vector of the tile objects that there can be layers of, the slope
       expected from the height and width is divided by mean to get the
       actual slope, and stddev is devietion from an exact triangle. */
    void canyon(int x, int y, int width, int height, 
        const vector<TileType> &fill, double mean, double stddev);

    // Make a mountain at x, y
    void mountain(int x, int y, int height);

    // Make an array containing the information for sinusoidal hills
    vector<double> makeHills(int length, int maxAmp, double maxFreq) const;

    // Actually put said sinusoidal hills on the map, adjusting for height
    void setHills(int start, int stop, int maxAmp, double maxFreq);

public:
    //  1-argument constructor
    World(WorldType worldType);

    // Destructor
    ~World();

    // Return the height of the map, in number of tiles
    int getHeight() const;

    // Return the width of the map, in number of tiles
    int getWidth() const;

    // Return the default spawn point
    Location getSpawn() const;

    // Returns the tile pointer at x, y
    // 0, 0 is the bottom right
    TileType getTile(int x, int y, TileType *array) const;

    // Set the tile at x, y equal to val
    void setTile(int x, int y, TileType val, TileType *array);

    // Write the map to a file
    void save(const string &filename) const;
};

#endif
