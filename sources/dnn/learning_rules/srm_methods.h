#pragma once

#include <snnlib/util/fastapprox/fastlog.h>

class SRMMethods {
public:
    static inline double LLH(const SRMNeuron &n) {
		return LLH_formula(n.fired(), n.getFiringProbability());
    }

    static inline double LLH_given_Y(const SRMNeuron &n, const double &fired) {
		return LLH_formula(fired, n.getFiringProbability());
    }

    static inline double dLLH_dw(const SRMNeuron &n, Synapse *syn) {
    	return dLLH_dw_formula(
    		n.getFiringProbability()
    	  , n.act_r.ifc().probDeriv(n.y)
    	  , n.getProbabilityModulation()
    	  , n.fired()
    	  , syn.getMembranePotential()
    	);
    }

    static inline double dLLH_dw_given_Y(const SRMNeuron &n, Synapse &syn, const double &fired) {
		return dLLH_dw_formula(
			n.getFiringProbability()
		  , n.act_f.ifc().probDeriv(n.y)
		  , n.getProbabilityModulation()
		  , n.fired()
		  , syn.getMembranePotential()
		 );
    }
private:
	static inline double LLH_formula(const double &fired, const double &p) {
		return fired*log(p) + (1 - fired) * log(1-p);
	}
	static inline double dLLH_dw_formula(const double &p, const double &p_stroke, const double &M, const double &fired, const double &x) {
		return (p_stroke/(p/M)) * (fired - p) * fabs(x);
	}
};
