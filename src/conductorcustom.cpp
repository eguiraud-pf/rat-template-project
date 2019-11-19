/* Rat - A heavilly vectorised and parallelised 
implementation of the Multi-Level Fast Multipole Method (MLFMM).
Copyright (C) 2017  Jeroen van Nugteren

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

// include header
#include "conductorcustom.hh"


// code specific to Rat
namespace rat{namespace mdl{

	// constructor
	ConductorCustom::ConductorCustom(){
		
	}

	// factory
	ShConductorCustomPr ConductorCustom::create(){
		return std::make_shared<ConductorCustom>();
	}

}}

