//===--- IndexSystemDelegate.h ----------------------------------*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2018 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//

#ifndef INDEXSTOREDB_INDEX_INDEXSYSTEMDELEGATE_H
#define INDEXSTOREDB_INDEX_INDEXSYSTEMDELEGATE_H

#include "IndexStoreDB/Index/StoreUnitInfo.h"
#include "llvm/Support/Chrono.h"
#include <memory>
#include <string>

namespace IndexStoreDB {
namespace index {
  struct StoreUnitInfo;
  class DependentFileOutOfDateTriggerHint;

typedef std::shared_ptr<DependentFileOutOfDateTriggerHint> DependentFileOutOfDateTriggerHintRef;

class DependentFileOutOfDateTriggerHint {
  std::string FilePath;

public:
  explicit DependentFileOutOfDateTriggerHint(StringRef filePath) : FilePath(filePath) {}

  static DependentFileOutOfDateTriggerHintRef create(StringRef filePath) {
    return std::make_shared<DependentFileOutOfDateTriggerHint>(filePath);
  }

  std::string originalFileTrigger();
  std::string description();
};

class INDEXSTOREDB_EXPORT IndexSystemDelegate {
public:
  virtual ~IndexSystemDelegate() {}

  /// Called when the datastore gets initialized and receives the number of available units.
  virtual void initialPendingUnits(unsigned numUnits) {}

  virtual void processingAddedPending(unsigned NumActions) {}
  virtual void processingCompleted(unsigned NumActions) {}

  virtual void processedStoreUnit(StoreUnitInfo unitInfo) {}

  virtual void unitIsOutOfDate(StoreUnitInfo unitInfo,
                               llvm::sys::TimePoint<> outOfDateModTime,
                               DependentFileOutOfDateTriggerHintRef hint,
                               bool synchronous = false) {}

private:
  virtual void anchor();
};

} // namespace index
} // namespace IndexStoreDB

#endif
