#include "R3BFi7Cal2Hit.h"

R3BFi7Cal2Hit::R3BFi7Cal2Hit(Bool_t a_is_calibrator, Int_t a_verbose)
  : R3BBunchedFiberCal2Hit("Fi7", a_verbose, VERTICAL, 2, 256, 1, a_is_calibrator)
{
}

R3BFi7Cal2Hit::~R3BFi7Cal2Hit()
{
}

UInt_t R3BFi7Cal2Hit::FixMistake(UInt_t a_fiber_id)
{
  UInt_t n_fiber_id = a_fiber_id;	
//  if (320 == a_fiber_id) {n_fiber_id = 336;std::cout << a_fiber_id << "->" << n_fiber_id << '\n';}
//  if (336 == a_fiber_id) {n_fiber_id = 320;std::cout << a_fiber_id << "->" << n_fiber_id << '\n';}
//  if (431 == a_fiber_id) {n_fiber_id = 447;std::cout << a_fiber_id << "->" << n_fiber_id << '\n';}
//  if (447 == a_fiber_id) {n_fiber_id = 431;std::cout << a_fiber_id << "->" << n_fiber_id << '\n';}
  return n_fiber_id;
}

ClassImp(R3BFi7Cal2Hit)
