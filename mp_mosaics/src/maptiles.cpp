/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* output = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> tile_vals(theTiles.size(), Point<3>());
    map<Point<3>, TileImage*> tilemap;
    for(size_t i = 0; i < theTiles.size(); i++) {
        tile_vals.at(i) = convertToXYZ(theTiles.at(i).getAverageColor());
        tilemap.insert(std::pair<Point<3>, TileImage*>(tile_vals.at(i), &(theTiles.at(i))));
    }
    KDTree<3> seeker(tile_vals);
    for(int row = 0; row < theSource.getRows(); row++) {
        for(int col = 0; col < theSource.getColumns(); col++) {
            Point<3> closest_color = seeker.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(row, col)));
            TileImage* closest_img = tilemap.at(closest_color);
            output->setTile(row, col, closest_img);
            //output.setTile();
        }
    }
    return output;
}

