enum ClassLevel {Freshman, Sophomore, Junior, Senior};

struct student_info {
    char name[64];
    unsigned long CWID;
    char major[64];
    enum ClassLevel class_level;
    char zip[7];
    char phoneNum[14];
    float gpa; 
};