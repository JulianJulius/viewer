#!/usr/bin/env python3

import os
import re
import glob
import subprocess

def validate_test_file_syntax(filepath):
    """Check if a test file has valid C++ syntax"""
    
    # Basic syntax checks
    with open(filepath, 'r') as f:
        content = f.read()
    
    issues = []
    
    # Check for malformed CHECK_MESSAGE calls
    malformed_checks = re.findall(r'CHECK_MESSAGE\([^)]*\([^)]*,\s*"[^"]*"\)[^)]*\);', content)
    if malformed_checks:
        issues.append(f"Malformed CHECK_MESSAGE calls: {len(malformed_checks)}")
    
    # Check for empty test cases
    empty_tests = re.findall(r'TEST_CASE\("[^"]+"\)\s*\{\s*\}', content)
    if empty_tests:
        issues.append(f"Empty test cases: {len(empty_tests)}")
    
    # Check for unmatched braces in TEST_CASE
    test_cases = re.findall(r'TEST_CASE\("[^"]+"\)\s*\{[^}]*\}', content, re.DOTALL)
    total_test_cases = len(re.findall(r'TEST_CASE\("[^"]+"\)', content))
    if len(test_cases) != total_test_cases:
        issues.append(f"Unmatched braces in test cases: {total_test_cases - len(test_cases)}")
    
    # Check for missing includes
    if 'memcmp(' in content and '#include <cstring>' not in content:
        issues.append("Missing #include <cstring> for memcmp")
    
    if 'std::min(' in content and '#include <algorithm>' not in content:
        issues.append("Missing #include <algorithm> for std::min")
    
    return issues

def main():
    test_files = glob.glob('/home/ubuntu/viewer-fork/indra/*/tests/*_test.cpp')
    
    total_files = len(test_files)
    files_with_issues = 0
    total_issues = 0
    
    print(f"Validating {total_files} test files...")
    
    for filepath in test_files:
        issues = validate_test_file_syntax(filepath)
        if issues:
            files_with_issues += 1
            total_issues += len(issues)
            print(f"\n{filepath}:")
            for issue in issues:
                print(f"  - {issue}")
    
    print(f"\nValidation Summary:")
    print(f"  Total files: {total_files}")
    print(f"  Files with issues: {files_with_issues}")
    print(f"  Total issues: {total_issues}")
    print(f"  Clean files: {total_files - files_with_issues}")

if __name__ == "__main__":
    main()
