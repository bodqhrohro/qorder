project('ua.ho.bodqhrohro.qorder', 'c', 'cpp',
        license: 'GPL3',
        default_options: ['c_std=c11', 'cpp_std=c++17'])

qt6 = import('qt6')

qt6_deps = dependency('qt6', modules: ['Core', 'Gui', 'Widgets'])

includes = include_directories('src')

qtprocessed = qt6.preprocess(moc_headers: ['src/mainwindow.h', 'src/actions_model.h'],
                             ui_files: 'src/mainwindow.ui',
                             include_directories: includes)

exe = executable('qorder', 'src/main.cpp', 'src/mainwindow.cpp', 'src/actions_model.cpp',
                 qtprocessed,
                 include_directories: includes,
                 dependencies: qt6_deps,
                 install: true)
