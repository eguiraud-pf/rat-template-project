// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <https://unlicense.org>

// DESCRIPTION
// Minimalist example of a solenoid model

// command line parser
#include <tclap/CmdLine.h>

// header files for common
#include "rat/common/log.hh"

// header files for model
#include "rat/models/pathcircle.hh"
#include "rat/models/crossrectangle.hh"
#include "rat/models/modelcoil.hh"
#include "rat/models/calcmesh.hh"

// main function
int main(int argc, char *argv[]){
	// create tclap object
	TCLAP::CmdLine cmd("Template",' ',"myversion");

	// filename input argument
	TCLAP::ValueArg<std::string> output_path_argument(
		"","od","output directory",false,"./data","string",cmd);

	// parse the command line arguments
	cmd.parse(argc, argv);

	// model geometric input parameters
	const rat::fltp time = 0; // output time [s]
	const rat::fltp radius = 40e-3; // coil inner radius [m]
	const rat::fltp dcoil = 10e-3; // thickness of the coil [m]
	const rat::fltp wcable = 12e-3; // width of the cable [m]
	const rat::fltp delem = 1e-3; // element size [m]
	const arma::uword num_sections = 4; // number of coil sections

	// model operating parameters
	const rat::fltp operating_current = 200; // operating current in [A]
	const arma::uword num_turns = 100; // number of turns

	// create logger
	const rat::cmn::ShLogPr lg = rat::cmn::Log::create(rat::cmn::Log::LogoType::RAT);

	// create a circular path object
	const rat::mdl::ShPathCirclePr circle = rat::mdl::PathCircle::create(radius, num_sections, delem);
	circle->set_offset(dcoil);

	// create a rectangular cross section object
	rat::mdl::ShCrossRectanglePr rectangle = rat::mdl::CrossRectangle::create(0, dcoil, 0, wcable, delem);

	// create a coil object
	const rat::mdl::ShModelCoilPr coil = rat::mdl::ModelCoil::create(circle, rectangle);
	coil->set_number_turns(num_turns);
	coil->set_operating_current(operating_current);

	// create calculation
	const rat::mdl::ShCalcMeshPr mesh_calculation = rat::mdl::CalcMesh::create(coil);

	// calculate everything
	mesh_calculation->calculate_write({time},output_path_argument.getValue(),lg);
}
