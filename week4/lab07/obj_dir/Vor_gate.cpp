// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vor_gate__pch.h"

//============================================================
// Constructors

Vor_gate::Vor_gate(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vor_gate__Syms(contextp(), _vcname__, this)}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , y{vlSymsp->TOP.y}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vor_gate::Vor_gate(const char* _vcname__)
    : Vor_gate(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vor_gate::~Vor_gate() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vor_gate___024root___eval_debug_assertions(Vor_gate___024root* vlSelf);
#endif  // VL_DEBUG
void Vor_gate___024root___eval_static(Vor_gate___024root* vlSelf);
void Vor_gate___024root___eval_initial(Vor_gate___024root* vlSelf);
void Vor_gate___024root___eval_settle(Vor_gate___024root* vlSelf);
void Vor_gate___024root___eval(Vor_gate___024root* vlSelf);

void Vor_gate::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vor_gate::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vor_gate___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vor_gate___024root___eval_static(&(vlSymsp->TOP));
        Vor_gate___024root___eval_initial(&(vlSymsp->TOP));
        Vor_gate___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vor_gate___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vor_gate::eventsPending() { return false; }

uint64_t Vor_gate::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vor_gate::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vor_gate___024root___eval_final(Vor_gate___024root* vlSelf);

VL_ATTR_COLD void Vor_gate::final() {
    Vor_gate___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vor_gate::hierName() const { return vlSymsp->name(); }
const char* Vor_gate::modelName() const { return "Vor_gate"; }
unsigned Vor_gate::threads() const { return 1; }
void Vor_gate::prepareClone() const { contextp()->prepareClone(); }
void Vor_gate::atClone() const {
    contextp()->threadPoolpOnClone();
}
