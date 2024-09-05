// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vand_gate__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vand_gate::Vand_gate(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vand_gate__Syms(contextp(), _vcname__, this)}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , y{vlSymsp->TOP.y}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vand_gate::Vand_gate(const char* _vcname__)
    : Vand_gate(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vand_gate::~Vand_gate() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vand_gate___024root___eval_debug_assertions(Vand_gate___024root* vlSelf);
#endif  // VL_DEBUG
void Vand_gate___024root___eval_static(Vand_gate___024root* vlSelf);
void Vand_gate___024root___eval_initial(Vand_gate___024root* vlSelf);
void Vand_gate___024root___eval_settle(Vand_gate___024root* vlSelf);
void Vand_gate___024root___eval(Vand_gate___024root* vlSelf);

void Vand_gate::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vand_gate::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vand_gate___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vand_gate___024root___eval_static(&(vlSymsp->TOP));
        Vand_gate___024root___eval_initial(&(vlSymsp->TOP));
        Vand_gate___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vand_gate___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vand_gate::eventsPending() { return false; }

uint64_t Vand_gate::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vand_gate::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vand_gate___024root___eval_final(Vand_gate___024root* vlSelf);

VL_ATTR_COLD void Vand_gate::final() {
    Vand_gate___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vand_gate::hierName() const { return vlSymsp->name(); }
const char* Vand_gate::modelName() const { return "Vand_gate"; }
unsigned Vand_gate::threads() const { return 1; }
void Vand_gate::prepareClone() const { contextp()->prepareClone(); }
void Vand_gate::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vand_gate::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vand_gate___024root__trace_decl_types(VerilatedVcd* tracep);

void Vand_gate___024root__trace_init_top(Vand_gate___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vand_gate___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vand_gate___024root*>(voidSelf);
    Vand_gate__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    if (strlen(vlSymsp->name())) tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vand_gate___024root__trace_decl_types(tracep);
    Vand_gate___024root__trace_init_top(vlSelf, tracep);
    if (strlen(vlSymsp->name())) tracep->popPrefix();
}

VL_ATTR_COLD void Vand_gate___024root__trace_register(Vand_gate___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vand_gate::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vand_gate::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vand_gate___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
