//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the LGPLv3 License.
*/

#pragma once

//IDA
#include <pro.h>

#include <map>
#include <set>

/* libTriton */
#include <api.hpp>
#include <ast.hpp>
#include <symbolicEngine.hpp>
#include <taintEngine.hpp>
#include <x8664Cpu.hpp>
#include <x86Cpu.hpp>

// Ponce
#include "runtime_status.hpp"

//! \class Snapshot
//! \brief the snapshot class.
class Snapshot {

private:
	//! I/O memory monitoring for snapshot.
	std::map<ea_t, char> memory;

	//! Status of the snapshot engine.
	bool locked;

	//! Status of the snapshot engine.
	bool snapshotTaken;

	//! Flag which defines if we must restore the snapshot.
	bool mustBeRestore;

	//! AST node state.
	std::set<triton::ast::AbstractNode*> nodesList;

	//! Variables node state.
	std::map<std::string, triton::ast::AbstractNode*> variablesMap;

	//! Snapshot of the symbolic engine.
	triton::engines::symbolic::SymbolicEngine *snapshotSymEngine;

	//! Snapshot of the taint engine.
	triton::engines::taint::TaintEngine *snapshotTaintEngine;

	//! Snapshot of triton CPU.
#if defined(__x86_64__) || defined(_M_X64)
	triton::arch::x86::x8664Cpu* cpu;
#endif
#if defined(__i386) || defined(_M_IX86)
	triton::arch::x86::x86Cpu* cpu;
#endif

	//! Snapshot of Pin context.
	std::map<std::string, triton::uint512> IDAContext;
	
	//! Snapshot of the ponce plugin status
	struct runtime_status_t saved_ponce_runtime_status;

	//! address where the snapshot was taken
	ea_t address;

public:
	//! Constructor.
	Snapshot();

	//! Destructor.
	~Snapshot();

	//! Returns true if the snapshot engine is disabled.
	bool isLocked(void);

	//! Returns true if we must restore the context.
	bool mustBeRestored(void);

	//! Adds a memory modifiction.
	void addModification(ea_t address, char byte);

	//! Disables the snapshot engine.
	void disableSnapshot(void);

	//! Resets the snapshot engine.
	void resetEngine(void);

	//! Restores a snapshot.
	void restoreSnapshot();

	//! Sets the restore flag.
	void setRestore(bool flag);

	//! Takes a snapshot.
	void takeSnapshot();

	//! Tells if a snapshot has been taken
	bool exists(void);

	//! Setter for the address where the snaphsot was taken
	void setAddress(ea_t address);
};

