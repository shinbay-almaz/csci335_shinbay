// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VOR_GATE__SYMS_H_
#define VERILATED_VOR_GATE__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vor_gate.h"

// INCLUDE MODULE CLASSES
#include "Vor_gate___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vor_gate__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vor_gate* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vor_gate___024root             TOP;

    // CONSTRUCTORS
    Vor_gate__Syms(VerilatedContext* contextp, const char* namep, Vor_gate* modelp);
    ~Vor_gate__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
