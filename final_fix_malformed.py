#!/usr/bin/env python3

import os
import re
import glob

def fix_malformed_check_messages(filepath):
    """Fix remaining malformed CHECK_MESSAGE calls"""
    
    with open(filepath, 'r') as f:
        content = f.read()
    
    original_content = content
    
    # Pattern 1: CHECK_MESSAGE(condition, "message", extra_stuff);
    content = re.sub(
        r'CHECK_MESSAGE\(([^,]+), "([^"]+)", ([^)]+)\);',
        r'CHECK_MESSAGE(\1, "\2");',
        content
    )
    
    # Pattern 2: CHECK_MESSAGE(condition == (type, "message") value);
    content = re.sub(
        r'CHECK_MESSAGE\(([^=]+)==\s*\(([^,]+),\s*"([^"]+)"\)\s*([^)]+)\);',
        r'CHECK_MESSAGE(\1== (\2) \4, "\3");',
        content
    )
    
    # Pattern 3: CHECK_MESSAGE(condition != (type, "message") value);
    content = re.sub(
        r'CHECK_MESSAGE\(([^!]+)!=\s*\(([^,]+),\s*"([^"]+)"\)\s*([^)]+)\);',
        r'CHECK_MESSAGE(\1!= (\2) \4, "\3");',
        content
    )
    
    # Pattern 4: More complex malformed patterns
    # CHECK_MESSAGE(condition, "message", more, stuff);
    content = re.sub(
        r'CHECK_MESSAGE\(([^,]+), "([^"]+)"(?:, [^)]+)*\);',
        r'CHECK_MESSAGE(\1, "\2");',
        content
    )
    
    # Pattern 5: Fix nested parentheses issues
    # Look for patterns like CHECK_MESSAGE((condition), ("message"), extra);
    content = re.sub(
        r'CHECK_MESSAGE\(\(([^)]+)\), \("([^"]+)"\)(?:, [^)]+)*\);',
        r'CHECK_MESSAGE(\1, "\2");',
        content
    )
    
    if content != original_content:
        with open(filepath, 'w') as f:
            f.write(content)
        return True
    
    return False

def main():
    # Get list of files with malformed CHECK_MESSAGE calls
    files_with_issues = [
        '/home/ubuntu/viewer-fork/indra/llcommon/tests/commonmisc_test.cpp',
        '/home/ubuntu/viewer-fork/indra/llcommon/tests/lazyeventapi_test.cpp',
        '/home/ubuntu/viewer-fork/indra/llcommon/tests/llallocator_heap_profile_test.cpp',
        '/home/ubuntu/viewer-fork/indra/llcommon/tests/lldate_test.cpp',
        '/home/ubuntu/viewer-fork/indra/llcommon/tests/lldeadmantimer_test.cpp',
        '/home/ubuntu/viewer-fork/indra/llcommon/tests/lldependencies_test.cpp',
        '/home/ubuntu/viewer-fork/indra/llcommon/tests/lleventdispatcher_test.cpp',
        '/home/ubuntu/viewer-fork/indra/llcommon/tests/llinstancetracker_test.cpp',
        '/home/ubuntu/viewer-fork/indra/llcommon/tests/llpounceable_test.cpp',
        '/home/ubuntu/viewer-fork/indra/llcommon/tests/llprocess_test.cpp',
        '/home/ubuntu/viewer-fork/indra/llcommon/tests/llsingleton_test.cpp',
        '/home/ubuntu/viewer-fork/indra/llcommon/tests/llstring_test.cpp',
        '/home/ubuntu/viewer-fork/indra/llcommon/tests/llunits_test.cpp'
    ]
    
    # Also process all test files to catch any we missed
    all_test_files = glob.glob('/home/ubuntu/viewer-fork/indra/*/tests/*_test.cpp')
    
    fixed_count = 0
    
    for filepath in all_test_files:
        if fix_malformed_check_messages(filepath):
            fixed_count += 1
            print(f"Fixed malformed CHECK_MESSAGE calls in: {os.path.basename(filepath)}")
    
    print(f"\nFixed {fixed_count} files")

if __name__ == "__main__":
    main()

