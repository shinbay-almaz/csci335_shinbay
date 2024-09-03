// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vor_gate.h for the primary calling header

#include "Vor_gate__pch.h"
#include "Vor_gate__Syms.h"
#include "Vor_gate___024root.h"

void Vor_gate___024root___ctor_var_reset(Vor_gate___024root* vlSelf);

Vor_gate___024root::Vor_gate___024root(Vor_gate__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vor_gate___024root___ctor_var_reset(this);
}

void Vor_gate___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vor_gate___024root::~Vor_gate___024root() {
}
