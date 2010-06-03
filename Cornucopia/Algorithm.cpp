/*--
    Algorithm.cpp  

    This file is part of the Cornucopia curve sketching library.
    Copyright (C) 2010 Ilya Baran (ibaran@mit.edu)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Algorithm.h"
#include "Preprocessing.h"
#include "CornerDetector.h"
#include "Debugging.h"
#include "Resampler.h"

using namespace std;
using namespace Eigen;
NAMESPACE_Cornu

std::vector<std::vector<AlgorithmBase *> > AlgorithmBase::_algorithms(NUM_ALGORITHM_STAGES);
bool AlgorithmBase::_initializationFinished = false;

const std::vector<std::vector<AlgorithmBase *> > &AlgorithmBase::_getAlgorithms()
{
    _initialize();
    return _algorithms;
}

void AlgorithmBase::_addAlgorithm(int stage, AlgorithmBase *algorithm)
{
    if(_initializationFinished)
    {
        Debugging::get()->printf("ERROR: Attempting to create algorithm too late!");
        return; //Noop
    }
    _algorithms[stage].push_back(algorithm);
}

void AlgorithmBase::_initialize()
{
    if(_initializationFinished)
        return;

    Algorithm<SCALE_DETECTION>::_initialize();
    Algorithm<CURVE_CLOSING>::_initialize();
    Algorithm<CORNER_DETECTION>::_initialize();
    Algorithm<RESAMPLING>::_initialize();

    _initializationFinished = true;
}

END_NAMESPACE_Cornu

