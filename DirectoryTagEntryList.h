//// /////////////////////////////////////////////  ////
 // Created by Rodion "rodde" Efremov on 20.11.2020. //
//// ////////////////////////////////////////////// ////

#ifndef COM_GITHUB_CODERODDE_DS4MAC_DIRECTORY_TAG_ENTRY_LIST_H
#define COM_GITHUB_CODERODDE_DS4MAC_DIRECTORY_TAG_ENTRY_LIST_H

#include "DirectoryTagEntry.h"
#include <vector>

namespace com::github::coderodde::ds4mac {

    class DirectoryTagEntryList {
    private:
        std::vector<DirectoryTagEntry> entries;

    public:
        auto begin() const {
            return entries.begin();
        }

        auto end() const {
            return entries.end();
        }

        size_t size() const;
        DirectoryTagEntryList& operator<<(
            DirectoryTagEntry const& directoryTagEntry);

        DirectoryTagEntry at(size_t index) const;
        DirectoryTagEntry* operator[](
            std::string const& targetDirectoryName);

        void sortByTags();
        void sortByDirectories();

        friend std::ostream&
          operator<<(std::ostream&,
                     DirectoryTagEntryList const&);


        friend std::istream& operator>>(
            std::istream& is,
            DirectoryTagEntryList& directoryTagEntryList);
    };
}

#endif // COM_GITHUB_CODERODDE_DS4MAC_DIRECTORY_TAG_ENTRY_LIST_H
