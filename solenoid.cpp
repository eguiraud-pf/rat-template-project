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

// header files for common
#include "rat/common/log.hh"

// header files for model
#include "rat/models/pathcircle.hh"
#include "rat/models/crossrectangle.hh"
#include "rat/models/modelcoil.hh"
#include "rat/models/calcmesh.hh"
#include "rat/models/modelmlfmm.hh"

// main
int main(){
	// model geometric input parameters
	const rat::fltp radius = RAT_CONST(40e-3); // coil inner radius [m]
	const rat::fltp dcoil = RAT_CONST(10e-3); // thickness of the coil [m]
	const rat::fltp wcable = RAT_CONST(12e-3); // width of the cable [m]
	const rat::fltp delem = RAT_CONST(2e-3); // element size [m]
	const arma::uword num_sections = 4; // number of coil sections

	// model operating parameters
	const rat::fltp operating_current = 200; // operating current in [A]
	const arma::uword num_turns = 100; // number of turns

	// create logger
	rat::cmn::ShLogPr lg = rat::cmn::Log::create();

	// create a circular path object
	rat::mdl::ShPathCirclePr circle = rat::mdl::PathCircle::create(radius, num_sections, delem);
	circle->set_offset(dcoil);

	// create a rectangular cross section object
	rat::mdl::ShCrossRectanglePr rectangle = rat::mdl::CrossRectangle::create(0, dcoil, 0, wcable, delem);

	// create a coil object
	rat::mdl::ShModelCoilPr coil = rat::mdl::ModelCoil::create(circle, rectangle);
	coil->set_number_turns(num_turns);
	coil->set_operating_current(operating_current);
	
	// create calculation
	rat::mdl::ShModelMlfmmPr mlfmm = rat::mdl::ModelMlfmm::create(coil);
	mlfmm->set_output_dir("./solenoid/");
	mlfmm->set_target_meshes(); // calculates field on surface
	
	// calculate everything
	mlfmm->calculate(lg);
}
