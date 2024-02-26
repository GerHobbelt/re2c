#ifndef _RE2C_CONF_OPT_
#define _RE2C_CONF_OPT_

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "src/constants.h"
#include "src/encoding/enc.h"
#include "src/options/symtab.h"
#include "src/options/syntax.h"
#include "src/util/attribute.h"
#include "src/util/forbid_copy.h"

namespace re2c {

// note [constant and mutable options]
//
// Some options are immutable (target, output files; global switches like conditions, reuse mode,
// storable states; support of flex syntax, etc.). These options are passed as command-line
// arguments and never change. It is safe to read them from any program point after parsing
// command-line arguments.
//
// Other options are configurable; they have block scope (may be specified anywhere inside of a
// block and still affect the whole block). Reading mutable options of yet unparsed block is not
// allowed because they may affect the way RE2C parses current block (RE2C would be tempted to base
// decisions on the latest option value, which may not be the final one).
//
// RE2C allows to set configurations anywhere inside of a block (in the beginning, intermixed with
// rules, in the end): they will affect the whole block anyway. Therefore it is not allowed to read
// configurations until the whole block has been parsed. Immutable options, on the other hand, are
// accessible for reading all the time (the parser itself depends on them).

class Input;
class Msg;
class Stx;

#define RE2C_SIGIL "@@"

// default backend is C
#ifndef RE2C_LANG
#define RE2C_LANG Lang::C
#endif

#define RE2C_CONSTOPTS \
    CONSTOPT(Target, target, Target::CODE) \
    CONSTOPT(CodeModel, code_model, CodeModel::GOTO_LABEL) \
    CONSTOPT(Enc::Type, input_encoding, Enc::Type::ASCII) \
    CONSTOPT(bool, date, true) \
    CONSTOPT(bool, version, true) \
    CONSTOPT(bool, start_conditions, false) \
    CONSTOPT(bool, storable_state, false) \
    CONSTOPT(bool, flex_syntax, false) \
    CONSTOPT(bool, verbose, false) \
    CONSTOPT(bool, line_dirs, true) \
    /* files */ \
    CONSTOPT(std::string, source_file, "") \
    CONSTOPT(std::string, output_file, "") \
    CONSTOPT(std::string, dep_file, "") \
    CONSTOPT(std::string, syntax_file, "") \
    CONSTOPT(std::vector<std::string>, include_paths, std::vector<std::string>()) \
    /* internals */ \
    CONSTOPT(Minimization, minimization, Minimization::MOORE) \
    CONSTOPT(PosixPrectable, posix_prectable, PosixPrectable::COMPLEX) \
    CONSTOPT(FixedTags, fixed_tags, FixedTags::ALL) \
    CONSTOPT(bool, optimize_tags, true) \
    CONSTOPT(bool, nested_negative_tags, true) \
    CONSTOPT(bool, eager_skip, false) \
    /* debug */ \
    CONSTOPT(bool, dump_nfa, false) \
    CONSTOPT(bool, dump_dfa_raw, false) \
    CONSTOPT(bool, dump_dfa_det, false) \
    CONSTOPT(bool, dump_dfa_tagopt, false) \
    CONSTOPT(bool, dump_dfa_min, false) \
    CONSTOPT(bool, dump_adfa, false) \
    CONSTOPT(bool, dump_cfg, false) \
    CONSTOPT(bool, dump_interf, false) \
    CONSTOPT(bool, dump_closure_stats, false) \
    CONSTOPT(bool, dump_dfa_tree, false) \
    /* end */

#define RE2C_MUTOPTS \
    /* header file */ \
    MUTOPT1(std::string, header_file, "") \
    /* regular expressions */ \
    MUTOPT(Enc,  encoding, Enc()) \
    MUTOPT(bool, case_insensitive, false) \
    MUTOPT(bool, case_inverted, false) \
    MUTOPT(EmptyClass, empty_class, EmptyClass::MATCH_EMPTY) \
    /* input API */ \
    MUTOPT(Api, api, Api::DEFAULT) \
    MUTOPT(ApiStyle, api_style, ApiStyle::FUNCTIONS) \
    MUTOPT(std::string, api_sigil, RE2C_SIGIL) \
    MUTOPT(std::string, api_char_type, "YYCTYPE") \
    MUTOPT(std::string, api_cursor, "YYCURSOR") \
    MUTOPT(std::string, api_marker, "YYMARKER") \
    MUTOPT(std::string, api_ctxmarker, "YYCTXMARKER") \
    MUTOPT(std::string, api_limit, "YYLIMIT") \
    MUTOPT(std::string, api_peek, "YYPEEK") \
    MUTOPT(std::string, api_skip, "YYSKIP") \
    MUTOPT(std::string, api_backup, "YYBACKUP") \
    MUTOPT(std::string, api_backup_ctx, "YYBACKUPCTX") \
    MUTOPT(std::string, api_restore, "YYRESTORE") \
    MUTOPT(std::string, api_restore_ctx, "YYRESTORECTX") \
    MUTOPT(std::string, api_restore_tag, "YYRESTORETAG") \
    MUTOPT(std::string, api_less_than, "YYLESSTHAN") \
    MUTOPT(std::string, api_stag_neg, "YYSTAGN") \
    MUTOPT(std::string, api_stag_pos, "YYSTAGP") \
    MUTOPT(std::string, api_mtag_neg, "YYMTAGN") \
    MUTOPT(std::string, api_mtag_pos, "YYMTAGP") \
    MUTOPT(std::string, api_shift, "YYSHIFT") \
    MUTOPT(std::string, api_shift_stag, "YYSHIFTSTAG") \
    MUTOPT(std::string, api_shift_mtag, "YYSHIFTMTAG") \
    MUTOPT(std::string, api_fill, "YYFILL") \
    MUTOPT(std::string, api_cond_type, "YYCONDTYPE") \
    MUTOPT(std::string, api_cond_get, "YYGETCONDITION") \
    MUTOPT(std::string, api_cond_set, "YYSETCONDITION" ) \
    MUTOPT(std::string, api_state_get, "YYGETSTATE") \
    MUTOPT(std::string, api_state_set, "YYSETSTATE") \
    MUTOPT(std::string, api_debug, "YYDEBUG") \
    MUTOPT(std::vector<std::string>, api_function, {}) \
    /* variables */ \
    MUTOPT(std::string, var_accept, "yyaccept") \
    MUTOPT(std::string, var_bitmaps, "yybm") \
    MUTOPT(std::string, var_cgoto_table, "yytarget") \
    MUTOPT(std::string, var_char, "yych") \
    MUTOPT(std::string, var_cond_table, "yyctable") \
    MUTOPT(std::string, var_state, "yystate") \
    /* code generation */ \
    MUTOPT(bool, bitmaps, false) \
    MUTOPT(bool, bitmaps_hex, false) \
    MUTOPT(bool, case_ranges, false) \
    MUTOPT(bool, cgoto, false) \
    MUTOPT(uint32_t, cgoto_threshold, 9) \
    MUTOPT(bool, nested_ifs, false) \
    MUTOPT(bool, unsafe, true) \
    /* YYFILL */ \
    MUTOPT(uint32_t, fill_eof, NOEOF) \
    MUTOPT(uint32_t, fill_sentinel, NOEOF) \
    MUTOPT(bool, fill_enable, true) \
    MUTOPT(bool, fill_check, true) \
    MUTOPT(std::string, fill_param, RE2C_SIGIL) \
    MUTOPT(bool, fill_param_enable, true) \
    MUTOPT(bool, fill_naked, false) \
    /* yych */ \
    MUTOPT(bool, char_emit, true) \
    MUTOPT(bool, char_conv, false) \
    /* conditions */ \
    MUTOPT(bool, cond_get_naked, false) \
    MUTOPT(std::string, cond_set_param, RE2C_SIGIL ) \
    MUTOPT(bool, cond_set_naked, false ) \
    MUTOPT(std::string, cond_label_prefix, "yyc_") \
    MUTOPT(std::string, cond_enum_prefix, "yyc") \
    MUTOPT(std::string, cond_div, "/* *********************************** */") \
    MUTOPT(std::string, cond_div_param, RE2C_SIGIL) \
    MUTOPT(std::string, cond_goto, "goto " RE2C_SIGIL ";") \
    MUTOPT(std::string, cond_goto_param, RE2C_SIGIL) \
    /* states */ \
    MUTOPT(bool, state_get_naked, false) \
    MUTOPT(std::string, state_set_param, RE2C_SIGIL) \
    MUTOPT(bool, state_set_naked, false) \
    MUTOPT(bool, state_abort, false) \
    MUTOPT(bool, state_next, false) \
    /* tags */ \
    MUTOPT(bool, tags, false) \
    MUTOPT(std::string, tags_expression, RE2C_SIGIL) \
    MUTOPT(bool, tags_automatic, false) \
    MUTOPT(bool, tags_history, false) \
    MUTOPT(bool, tags_posix_syntax, false) \
    MUTOPT(bool, tags_posix_semantics, false) \
    MUTOPT(std::string, tags_prefix, "yyt") \
    MUTOPT(bool, invert_captures, false) \
    /* labels */ \
    MUTOPT(std::string, label_fill, "yyFillLabel") \
    MUTOPT(std::string, label_loop, "") \
    MUTOPT(std::string, label_next, "yyNext") \
    MUTOPT(std::string, label_prefix, "yy") \
    MUTOPT(std::string, label_start, "") \
    MUTOPT(bool, label_start_force, false) \
    /* formatting */ \
    MUTOPT(uint32_t, indent_top, 0) \
    MUTOPT(std::string, indent_str, "\t") \
    /* debug */ \
    MUTOPT(bool, debug, false) \
    /* end */

// variables in syntax files
#define RE2C_STX_VARS \
    STX_VAR("nl") \
    STX_VAR("indent") \
    STX_VAR("dedent") \
    STX_VAR("topindent")

// Constant options.
struct conopt_t {
  private:
    const Stx& stx;

  public:
    // Global options are public (for easier read access), but constant (to avoid
    // accidental write access, as this should be done by `set_*` methods that correctly
    // update `is_default_*` status).
#define CONSTOPT(type, name, value) const type name;
    RE2C_CONSTOPTS
#undef CONSTOPT
#define CONSTOPT(type, name, value) bool is_default_##name;
    RE2C_CONSTOPTS
#undef CONSTOPT

    conopt_t(const Stx& stx)
        : stx(stx)
#define CONSTOPT(type, name, value) , name(value)
    RE2C_CONSTOPTS
#undef CONSTOPT
#define CONSTOPT(type, name, value) , is_default_##name(true)
    RE2C_CONSTOPTS
#undef CONSTOPT
    {}

#define CONSTOPT(type, name, value) \
    void set_##name(type val) { \
        const_cast<type&>(name) = val; \
        is_default_##name = false; \
    } \
    void set_default_##name(type val) { \
        const_cast<type&>(name) = val; \
        is_default_##name = true; \
    }
    RE2C_CONSTOPTS
#undef CONSTOPT

    // forward methods from `Stx` to make them easier to use from lexer
    inline const char* eval_word_conf(const char* name) const {
        return stx.eval_word_conf(name);
    }
    inline bool eval_bool_conf(const char* name) const {
        return stx.eval_bool_conf(name);
    }

    FORBID_COPY(conopt_t);
};

// Mutable options.
struct mutopt_t {
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) type name;
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT

    mutopt_t()
#define MUTOPT1(type, name, value) : name(value)
#define MUTOPT(type, name, value)  , name(value)
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT
    {}
    FORBID_COPY(mutopt_t);
};

// Boolean flags for mutable options.
struct mutdef_t {
#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) bool name;
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT

    mutdef_t()
#define MUTOPT1(type, name, value) : name(true)
#define MUTOPT(type, name, value)  , name(true)
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT
    {}
};

// Union of constant and mutable options and default flags.
struct opt_t {
  private:
    const Stx& stx;

  public:
#define CONSTOPT(type, name, value) type name;
    RE2C_CONSTOPTS
#undef CONSTOPT

#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) type name;
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTOPT(type, name, value) bool is_default_##name;
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT
    symtab_t symtab;

    opt_t(const Stx& stx,
            const conopt_t& con,
            const mutopt_t& mut,
            const mutdef_t& def,
            const symtab_t& symtab)
    : stx(stx)
#define CONSTOPT(type, name, value) , name(con.name)
    RE2C_CONSTOPTS
#undef CONSTOPT

#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) , name(mut.name)
    RE2C_MUTOPTS
#undef MUTOPT
#define MUTOPT(type, name, value) , is_default_##name(def.name)
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT
    , symtab(symtab)
    {}

    // forward methods from `Stx` to make them easier to use from codegen
    inline void eval_code_conf(std::ostream& os, const char* name, RenderCallback& callback) const {
        stx.eval_code_conf(os, this, name, callback);
    }
    inline void eval_code_conf(std::ostream& os, const char* name) const {
        stx.eval_code_conf(os, this, name);
    }
    inline const char* eval_word_conf(const char* name) const {
        return stx.eval_word_conf(name);
    }
    inline bool eval_bool_conf(const char* name) const {
        return stx.eval_bool_conf(name);
    }
    bool specialize_oneline_if() const { return stx.have_oneline_if; }
    bool specialize_oneline_switch() const { return stx.have_oneline_switch; }

    FORBID_COPY(opt_t);
};

// Options management.
struct Opt {
  public:
    Stx stx;
    const conopt_t glob;
    symtab_t symtab;
    Msg& msg;

  private:
    // Default mutable options. They depend on the global options, such as the language backend, and
    // are fixed after parsing the global options.
    const mutopt_t defaults;

    // Boolean flags indicating if a mutable option has been set by the user. These are needed to
    // distingush default values from user-set values that coincide with default ones. Constant and
    // mutable options passed on the command line may be intermixed (there is no ordering
    // requirement), so mutable options may be applied before all constant options are known and
    // default values for mutable options are determined. Such user-set mutable options should not
    // be altered by fixing default options.
    mutdef_t is_default;

    // User-set mutable options.
    mutopt_t user;

    // Real mutable options ("fixed" user-set options with various filters and implications that
    // make options consistent).
    mutopt_t real;

    // If user-set options have diverged from the real ones and need syncing.
    bool diverge;

  public:
    Opt(OutAllocator& alc, Msg& msg);
    const conopt_t& global() const { return glob; }
    Ret parse(char** argv, Input& input);
    Ret snapshot(const opt_t** opts) NODISCARD;
    Ret fix_global_and_defaults() NODISCARD;
    Ret restore(const opt_t* opts) NODISCARD;
    Ret merge(const opt_t* opts, Input& input) NODISCARD;

#define MUTOPT1 MUTOPT
#define MUTOPT(type, name, value) \
    void init_##name(const type &arg); \
    void set_##name(const type &arg); \
    void reset_##name();
    RE2C_MUTOPTS
#undef MUTOPT1
#undef MUTOPT
    void init_encoding(Enc::Type type, bool on);
    void init_encoding_policy(Enc::Policy p);
    void set_encoding(Enc::Type type, bool on);
    void set_encoding_policy(Enc::Policy p);

    void reset_group_label_start();

  private:
    Ret sync() NODISCARD;
    FORBID_COPY(Opt);
};

Ret parse_opts(char** argv, conopt_t& globopts, Opt& opts, Msg& msg) NODISCARD;

} // namespace re2c

#endif // _RE2C_CONF_OPT_
