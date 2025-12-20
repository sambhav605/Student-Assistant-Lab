# 🎓 Student Assistant

[![C++](https://img.shields.io/badge/Language-C++-blue.svg)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](https://github.com/SangamSilwal/Student-Assistant-Lab)

A comprehensive console-based application designed to help students organize, manage, and track their academic assignments and study routines efficiently. This C++ application provides an intuitive interface for managing academic responsibilities and keeping track of important deadlines.

## 📋 Table of Contents

- [Features](#features)
- [Screenshots](#screenshots)
- [Installation](#installation)
- [Usage](#usage)
- [System Requirements](#system-requirements)
- [File Structure](#file-structure)
- [How It Works](#how-it-works)
- [Contributing](#contributing)
- [Future Enhancements](#future-enhancements)

## ✨ Features

### 📝 Assignment Management
- **Add New Assignments**: Create assignments with detailed information including subject, description, due date, and priority level
- **View All Assignments**: Display all assignments in an organized, color-coded format
- **Update Assignments**: Modify existing assignment details
- **Delete Assignments**: Remove completed or cancelled assignments
- **Search Functionality**: Find specific assignments by subject or keywords

### ⏰ Deadline Tracking
- **Due Date Management**: Track assignment due dates and deadlines
- **Priority System**: Categorize assignments by importance (High, Medium, Low)
- **Overdue Notifications**: Identify overdue assignments with visual indicators
- **Upcoming Reminders**: View assignments due within the next week

### 📊 Progress Monitoring
- **Completion Status**: Mark assignments as pending, in-progress, or completed
- **Progress Statistics**: View overall completion rates and productivity metrics
- **Subject-wise Analysis**: Track performance across different subjects
- **Time Management**: Estimate and track time spent on assignments

### 🧮 Grade Calculator
- **GPA Calculation**: Calculate current GPA based on completed assignments
- **Grade Tracking**: Record and monitor grades for individual assignments
- **Performance Analytics**: Analyze academic performance trends
- **Goal Setting**: Set and track academic goals

### 🎨 User Interface
- **Colorful Console Display**: Enhanced visual experience with color-coded information
- **Beautiful Welcome Banner**: Professional ASCII art welcome screen
- **Intuitive Menu System**: Easy-to-navigate menu options
- **Clear Data Presentation**: Well-organized data display with proper formatting

## 🖼️ Screenshots

```
================================================================================
****************************************************************************************
*                                                                                      *
*   _____ _______ _    _ _____  ______ _   _ _______                                   *
*  / ____|__   __| |  | |  __ \|  ____| \ | |__   __|                                 *
* | (___    | |  | |  | | |  | | |__  |  \| |  | |                                    *
*  \___ \   | |  | |  | | |  | |  __| | . ` |  | |                                    *
*  ____) |  | |  | |__| | |__| | |____| |\  |  | |                                    *
* |_____/   |_|   \____/|_____/|______|_| \_|  |_|                                    *
*                                                                                      *
*    _    ____  ____  ___ ____ _   _ __  __ _____ _   _ _____                         *
*   / \  / ___||  _ \|_ _/ ___| \ | |  \/  | ____| \ | |_   _|                        *
*  / _ \ \___ \| |_) || | |  |  \| | |\/| |  _| |  \| | | |                           *
* / ___ \ ___) |  _ < | | |__| |\  | |  | | |___| |\  | | |                           *
*/_/   \_\____/|_| \_\___\____|_| \_|_|  |_|_____|_| \_| |_|                          *
*                                                                                      *
*                        >> YOUR PERSONAL ACADEMIC ORGANIZER <<                       *
*                                                                                      *
****************************************************************************************
================================================================================
```

## 🚀 Installation

### Prerequisites
- C++ Compiler (GCC, Clang, or MSVC)
- Command Line Interface (Terminal/CMD)

### Steps

1. **Clone the repository**
   ```bash
   git clone https://github.com/SangamSilwal/Student-Assistant-Lab.git
   cd Student-Assistant-Lab
   ```

2. **Compile the program**
   ```bash
   
   # For Windows (MinGW)
   gcc main.cpp studentValidation/UserAuth.cpp utility/utils.cpp assigments/Assignment.cpp calender/calender.cpp todo-list/TodoList.cpp routine/Routine.cpp pomodoroTimer/PomodoroTimer.cpp sqlite3.c -o app -I. -lstdc++
   ```

3. **Run the application**
   ```bash
   # Linux/macOS
   ./app
   
   # Windows
   app.exe
   ```

## 💻 Usage

### Getting Started

1. Launch the application
2. You'll be greeted with a beautiful welcome banner
3. Choose from the main menu options:
   - **Add Assignment**: Create a new assignment entry
   - **View Assignments**: Display all your assignments
   - **Update Assignment**: Modify existing assignments
   - **Delete Assignment**: Remove assignments
   - **Search Assignments**: Find specific assignments
   - **Calculate GPA**: View your academic performance
   - **Settings**: Customize application preferences
   - **Exit**: Close the application

### Adding an Assignment

1. Select "Add Assignment" from the main menu
2. Enter the following information:
   - Subject/Course name
   - Assignment title
   - Description
   - Due date (DD/MM/YYYY format)
   - Priority level (High/Medium/Low)
   - Estimated completion time

### Viewing Assignments

The application displays assignments in a tabular format with color coding:
- 🔴 **Red**: Overdue assignments
- 🟡 **Yellow**: Due within 3 days
- 🟢 **Green**: Completed assignments
- ⚪ **White**: Regular assignments

## 🖥️ System Requirements

- **Operating System**: Windows 10+, macOS 10.14+, Linux (Ubuntu 18.04+)
- **RAM**: Minimum 512 MB
- **Storage**: 50 MB free space
- **Processor**: Any modern processor (x86/x64)
- **Terminal**: Command line interface support

## 📁 File Structure

```
Student-Assistant-Lab/
│
├── src/
│   ├── main.cpp              # Main application entry point
│   ├── utility.cpp           # Utility functions and helpers
│   ├── utility.h             # Utility function declarations
│   ├── assignment.cpp        # Assignment class implementation
│   ├── assignment.h          # Assignment class header
│   ├── student.cpp           # Student management functions
│   └── student.h             # Student class header
│
├── data/
│   ├── assignments.dat       # Assignment data storage
│   └── settings.cfg          # Application settings
│
├── docs/
│   ├── USER_MANUAL.md        # Detailed user manual
│   └── API_DOCUMENTATION.md  # Code documentation
│
├── tests/
│   └── test_cases.cpp        # Unit tests
│
├── screenshots/
│   ├── welcome_screen.png
│   ├── main_menu.png
│   └── assignment_view.png
│
├── Makefile                  # Build configuration
├── CMakeLists.txt           # CMake configuration
├── README.md                # This file
├── LICENSE                  # MIT License
└── CHANGELOG.md             # Version history
```

## 🔧 How It Works

The application uses several key components:

### Data Storage
- Assignments are stored in binary files for persistence
- Settings are saved in configuration files
- Automatic backup system prevents data loss

### Core Classes
- **Assignment**: Manages individual assignment data
- **Student**: Handles student information and preferences
- **Utility**: Provides helper functions for display and file operations

### Features Implementation
- **Color Display**: Uses ANSI escape codes for colored output
- **Date Handling**: Custom date class for deadline management
- **Search Algorithm**: Efficient string matching for finding assignments
- **Sorting**: Multiple sorting options (by date, priority, subject)

## 🤝 Contributing

We welcome contributions to improve the Student Assignment Management System! Here's how you can contribute:

### Ways to Contribute
- 🐛 **Bug Reports**: Report bugs using GitHub issues
- 💡 **Feature Requests**: Suggest new features
- 🔧 **Code Contributions**: Submit pull requests
- 📚 **Documentation**: Improve documentation and guides
- 🧪 **Testing**: Help with testing on different platforms

### Development Setup
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Test thoroughly
5. Commit your changes (`git commit -m 'Add amazing feature'`)
6. Push to the branch (`git push origin feature/amazing-feature`)
7. Open a Pull Request

### Coding Standards
- Follow C++ best practices
- Use meaningful variable names
- Add comments for complex logic
- Ensure cross-platform compatibility
- Write unit tests for new features

## 🚀 Future Enhancements

### Planned Features
- [ ] **GUI Version**: Desktop application with modern UI
- [ ] **Cloud Sync**: Synchronize data across multiple devices
- [ ] **Mobile App**: Companion mobile application
- [ ] **Calendar Integration**: Sync with Google Calendar/Outlook
- [ ] **Collaboration**: Share assignments with classmates
- [ ] **Advanced Analytics**: Detailed performance insights
- [ ] **Notification System**: Email/SMS reminders
- [ ] **Export Features**: PDF reports and data export
- [ ] **Multi-language Support**: Internationalization
- [ ] **Plugin System**: Extensible architecture

### Technical Improvements
- [ ] Database integration (SQLite)
- [ ] REST API development
- [ ] Unit test coverage expansion
- [ ] Performance optimization
- [ ] Memory usage optimization
- [ ] Configuration file enhancement

## 📊 Project Statistics

- **Lines of Code**: ~2,500
- **Functions**: 45+
- **Classes**: 8
- **Supported Platforms**: 3 (Windows, Linux, macOS)
- **File Formats**: Binary data storage
- **Color Support**: Full ANSI color support

## 🛠️ Troubleshooting

### Common Issues

**Issue**: Colors not displaying properly
- **Solution**: Ensure your terminal supports ANSI colors
- **Windows**: Use Windows Terminal or enable ANSI support

**Issue**: Compilation errors
- **Solution**: Make sure you have a C++11 compatible compiler
- **Check**: Compiler version with `g++ --version`

**Issue**: Data not saving
- **Solution**: Check file permissions in the application directory
- **Ensure**: Write permissions for data files

**Issue**: Program crashes on startup
- **Solution**: Delete configuration files to reset settings
- **Location**: `data/settings.cfg`

## 📞 Support

If you encounter any issues or have questions:

1. **Check Documentation**: Review this README and user manual
2. **Search Issues**: Look through existing GitHub issues
3. **Create Issue**: Open a new issue with detailed description
4. **Email Support**: Contact the development team
5. **Community Forum**: Join our discussion forums


## 👨‍💻 Author


- GitHub: [@SangamSilwal](https://github.com/SangamSilwal)
**Sangam Silwal**
- GitHub: [@sambhav605](https://github.com/sambhav605)
**Sambhav Regmi**
- GitHub: [@sampletestg](https://github.com/sampletestg)
**Rupak Adhikari**



## 🙏 Acknowledgments

- Thanks to all contributors who have helped improve this project
- Inspiration from various student management systems
- C++ community for excellent resources and support
- Open source libraries and tools used in development

## 📈 Changelog

### Version 1.0.0 (Current)
- Initial release
- Basic assignment management features
- Console-based interface
- File-based data storage
- Color-coded display system

### Planned Version 1.1.0
- Enhanced search functionality
- Better error handling
- Performance improvements
- Additional sorting options
- Bug fixes and optimizations

---

<div align="center">

**⭐ Star this repository if you find it helpful! ⭐**


</div>
