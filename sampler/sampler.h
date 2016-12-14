#ifndef _SAMPLER_H_
#define _SAMPLER_H_

#include <cstdlib>
#include <boost/random.hpp>

namespace Tools{
  /* The Sampler provides different methods to sample from
   * a normal distribution.
   */
  class Sampler{
  public:  
    Sampler();
    ~Sampler();

    // sample indices.size() indices from weight vector
    // using stochastic universal resampling
    // assuming the weights have values in [0,1]
    // but are not necessarily normalized (i.e. sum up to 1)
    static void resample(const std::vector<double>& weights, std::vector<size_t>& indices);
  
    // create a sample from a uniform distribution between min and max
    // using a boost mt19937 uniform distribution generator
    float sampleFromUniformDistribution(const float& min_, const float& max_);
    // create a sample from a uniform distribution between min and max
    // including min and excluding max
    // using a boost mt19937 uniform distribution generator
    int sampleIntFromUniformDistribution(const int& min_, const int& max_);

    // create a sample from a normal distribution given by the mean and the standard deviation sigma 
    // using a boost taus88 normal distribution generator
    float sampleFromNormalDistribution(float mean, float sigma);    

    // create a sample from a triangular distribution given by the mean and the width 
    float sampleFromTriangularDistribution(float mean, float width);

  protected:
    // parameters for sampling from a uniform distribution between 0 and 1
    boost::mt19937 _uniformDistributionSeedZero;
    boost::uniform_real<float> _uniformDistributionZero;
    boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > _uniformDistributionGeneratorZero;

    // parameters for sampling from a normal distribution
    boost::taus88 _normalDistributionSeed;
    boost::normal_distribution<float> _normalDistribution;
    boost::variate_generator<boost::taus88&, boost::normal_distribution<float> > _normalDistributionGenerator;

  };
};

#endif //_SAMPLER_H_

