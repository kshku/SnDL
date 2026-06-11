# Changelog

## [0.1.0] — 2026-06-11

## [0.0.0] — 2026-01-11

### Added
- Cross-platform shared library loading (`sn_dl_open`, `sn_dl_close`, `sn_dl_sym`)
- POSIX backend (`dlopen` / `dlsym` / `dlclose`)
- Windows backend (`LoadLibraryW` / `GetProcAddress` / `FreeLibrary`)
- User-provided error buffer for diagnostic messages
- Test suite with shared library loading verification
- CI workflows (Linux, macOS, Windows, formatting)
