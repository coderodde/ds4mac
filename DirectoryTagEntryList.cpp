//// ////////////////////////////////////////////// ////
 // Created by Rodion "rodde" Efremov on 20.11.2020. //
//// ////////////////////////////////////////////// ////

#include "DirectoryTagEntry.h"
#include "DirectoryTagEntryList.h"
#include <algorithm>
#include <limits>
#include <string>
#include <stdexcept>
//#include <linux/limits.h>

using com::github::coderodde::ds4mac::DirectoryTagEntry;
using std::getline;
using std::string;

namespace com::github::coderodde::ds4mac {

    size_t DirectoryTagEntryList::size() const {
        return entries.size();
    }

    DirectoryTagEntryList& DirectoryTagEntryList::operator<<(
        const DirectoryTagEntry &directoryTagEntry) {
    
        entries.push_back(directoryTagEntry);
        return *this;
    }

    DirectoryTagEntry DirectoryTagEntryList::at(size_t index) const {
        return entries.at(index);
    }

    DirectoryTagEntry* DirectoryTagEntryList::operator[](
        const std::string& targetDirectoryName) {
    
        DirectoryTagEntry* ptrBestDirectoryEntry;
        size_t bestLevenshteinDistance = std::numeric_limits<size_t>::max();

        for (DirectoryTagEntry& dte : entries) {
            size_t levenshteinDistance = dte.getLevenshteinDistance(targetDirectoryName);

            if (levenshteinDistance == 0) {
                return &dte;
            }

            if (bestLevenshteinDistance > levenshteinDistance) {
                bestLevenshteinDistance = levenshteinDistance;
                ptrBestDirectoryEntry = &dte;
            }
        }

        return ptrBestDirectoryEntry;
    }

    void DirectoryTagEntryList::sortByTags() {
        std::stable_sort(entries.begin(), entries.end(), DirectoryTagEntry::tagComparator);
    }

    void DirectoryTagEntryList::sortByDirectories() {
        std::stable_sort(entries.begin(), entries.end(),  DirectoryTagEntry::directoryComparator);
    }

    // trim from start (in place)
    static inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    // trim from both ends (in place)
    static inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

    std::istream& operator>>(
        std::istream& is,
        DirectoryTagEntryList& directoryTagEntryList) {

        while (!is.eof() && is.good()) {
            string tag;
            is >> tag;
            trim(tag);

            string dir;
            getline(is, dir);
            trim(dir);

            DirectoryTagEntry newDirectoryEntry(tag, dir);
            directoryTagEntryList << newDirectoryEntry;
        }

        if (!is.eof())
            throw std::runtime_error("istream failed");

        return is;
    }

    std::ostream& operator<<(
        std::ostream& os,
        DirectoryTagEntryList const& dtel) {
        size_t index = 0;

        for (auto &entry : dtel) {
            os << entry.getTagName() << " " << entry.getDirectoryName();

            if (index < dtel.size() - 1) {
                os << '\n';
            }
        }

        if (os.fail()) 
            throw std::runtime_error("ostream failed");

        return os;
    }
}