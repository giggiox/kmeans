//
// Created by luigi on 31/01/24.
//

#include <vector>
#include <cfloat>
#include "iostream"
#include "KMeans.h"
#include "centroid.h"
#include <cmath>
#include <random>

KMeans::KMeans(int k) {
    this->k = k;
}

double KMeans::euclideanNorm(Point &p1, Centroid &p2) {
    double squareSum = 0;
    int dimension = p1.coords.size();
    for(int i = 0;i<dimension; ++i){
        squareSum += (p1.coords[i]-p2.coords[i]) * (p1.coords[i]-p2.coords[i]);
    }
    return squareSum;
}

void KMeans::assignRandomCentroids(std::vector<Point>& dataPoints){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,dataPoints.size()-1);

    //std::vector<Point> centroids;
    for(int i = 0;i<this->k;++i){
        Point p = dataPoints[dist6(rng)];
        int dimension = p.coords.size();
        double coords[dimension];
        for(int j = 0;j<dimension;++j){
            coords[j] = p.coords[j];
        }
        this->centroids.push_back(Centroid(coords));
    }
}

void KMeans::fit(std::vector<Point>& dataPoints, int maxIteration, bool useStopCondition) {
    if(this->centroids.empty()){
        std::cerr << "assign centroids first" << std::endl;
        return;
    }

    for (int _ = 0; _ < maxIteration;++_) {
        std::vector<Centroid> newCentroids = std::vector<Centroid>(this->k, Centroid());
        for (Point& p: dataPoints) {
            double minDistance = DBL_MAX;
            for (int j = 0; j < this->k; ++j) {
                double distance = euclideanNorm(p, this->centroids[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    p.clusterLabel = j;
                }
            }
            for (int j = 0; j < dataPoints[0].coords.size(); ++j){
                newCentroids[p.clusterLabel].coords[j] += p.coords[j];
            }
            newCentroids[p.clusterLabel].cardinality += 1;
        }
        bool converged = true;
        for (int i = 0; i < this->k; i++) {
            for (int j = 0; j < dataPoints[0].coords.size(); ++j) {
                newCentroids[i].coords[j] /= newCentroids[i].cardinality;
                if (useStopCondition && std::abs(centroids[i].coords[j] - newCentroids[i].coords[j]) > 1e-15) {
                    converged = false;
                }
            }
            newCentroids[i].cardinality = 0;
        }

        if(useStopCondition && converged) {
            std::cout << "stopped at iter: ";
            std::cout << _ << std::endl;
            return;
        }

        this->centroids = newCentroids;
    }
}
