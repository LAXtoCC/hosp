#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
 
// 定义结构体保存用户信息
typedef struct {
    char username[20];
    char password[20];
    char phone[15];
    char id_card[18];
} User;
 
// 定义结构体保存医生信息
typedef struct {
    char name[30];
    char department[20];
    int is_specialist; // 1: 专家医生，0: 普通医生
    float registration_fee;
} Doctor;

 typedef struct {
 	char his1[100];
 	char his2[100];
}h ;
 
// 在全局定义科室数组
const char* departments[] = {
    "急诊科", "内科", "外科", "儿科", "妇科",
    "眼科", "耳鼻喉科", "口腔科", "皮肤科"
};
const int NUM_DEPARTMENTS = sizeof(departments) / sizeof(departments[0]);
 
 
// 定义结构体保存挂号信息
typedef struct {
    char username[20];
    char doctor_name[30];
    char department[20];
    char time_slot[20];
} Registration;
 typedef struct {
    char name[50];
    float price;
} Medicine;

Medicine medicines[] = {
    {"感冒药", 10.0},
    {"止咳糖浆", 15.0},
    {"消炎药", 20.0},
    {"降压药", 25.0},
    {"止痛片", 30.0},
    {"抗生素", 35.0},
    {"维生素", 40.0},
    {"钙片", 45.0},
    {"安眠药", 50.0},
    {"补血药", 55.0}
};
const int NUM_MEDICINES = sizeof(medicines) / sizeof(medicines[0]);

// 定义结构体保存待支付费用信息
typedef struct {
    char username[20];
    float amount_due;
} Payment;

Payment payments[100];
int payment_count = 0;

// 定义数组保存用户、医生和挂号信息
User users[100];
Doctor doctors[20];
Registration registrations[100];
int user_count = 0;
int doctor_count = 0;
int registration_count = 0;
h history1[100];
h history2[100];
int m=1,n=1;
 
// 函数声明
int registerUser();
int loginUser();
void showDepartments();
void showDoctors(char department[]);
int makeAppointment(char username[], char time_slot[20]);
void viewRegistrationDetails(char username[]);
int viewRegistrationHistory(char username[]);
void cancelAppointment(char username[]);
void giveFeedback();
void seeDoctor(char username[]);
void makePayment(char username[]);
void hospitalmanagement(char username[]);
void history();
void location();
 
int main() {
    char choice1;
    char choice2;
    // 添加张医生信息（专家医生）到所有科室
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        strcpy(doctors[doctor_count].name, "张医生");
        strcpy(doctors[doctor_count].department, departments[i]);
        doctors[doctor_count].is_specialist = 1;
        doctors[doctor_count].registration_fee = 50.0;
        doctor_count++;
    }
    // 添加李医生信息（普通医生）到所有科室
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        strcpy(doctors[doctor_count].name, "李医生");
        strcpy(doctors[doctor_count].department, departments[i]);
        doctors[doctor_count].is_specialist = 0;
        doctors[doctor_count].registration_fee = 30.0;
        doctor_count++;
    }
 
    while (1) {
    	system("cls");
        printf("\033[33m");  // 输出黄色文本
    	printf("\n#################################################################################\n");
    	printf("\n▓                          * 医院线上交互平台  *                           ▓\n");
    	printf("\n*********************************************************************************\n");
    	printf("\n          ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
	    printf("          |◆|******|◆|                                     |◆|******|◆|\n");
	    printf("          |◆|******|◆|       ☆ 注册    请按 1         |◆|******|◆|\n"); 
	    printf("          |◆|******|◆|       ☆ 登录    请按 2         |◆|******|◆|\n");
	 	printf("          |◆|******|◆|       ☆ 退出    请按 3         |◆|******|◆|\n");
	 	printf("          |◆|******|◆|                                     |◆|******|◆|\n");
	 	printf("          ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
	 	printf("\n#################################################################################\n");
        printf("\033[0m"); // 重置文本颜色
        scanf("%s", &choice1);
 
        switch (choice1) {
            case '1':
                registerUser();
                printf("按Enter继续进入菜单");
				getch(); 
                break;
            case '2':
                if (loginUser()) {
                    int loggedIn = 1;
                    while (loggedIn) {
                    	system("cls");
                    	printf("\033[31m"); // 设置文本颜色为红色
		              	printf("\n#################################################################################\n");
					    printf("\n▓                               * 欢迎使用  *                                 ▓\n");
					    printf("\n#################################################################################\n");
					 	printf("\n          ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n"); 
					 	printf("         |◆|******|◆|        ☆ 预约挂号       请按 1        |◆|******|◆|\n"); 
						printf("         |◆|******|◆|        ☆ 查询挂号       请按 2        |◆|******|◆|\n");
					 	printf("         |◆|******|◆|        ☆ 取消预约       请按 3        |◆|******|◆|\n"); 
						printf("         |◆|******|◆|        ☆ 反馈和评价     请按 4        |◆|******|◆|\n");
					    printf("         |◆|******|◆|        ☆ 看病           请按 5        |◆|******|◆|\n");
					 	printf("         |◆|******|◆|        ☆ 缴费           请按 6        |◆|******|◆|\n"); 
					 	printf("         |◆|******|◆|        ☆ 住院管理       请按 7        |◆|******|◆|\n"); 
					 	printf("         |◆|******|◆|        ☆ 导航           请按 8        |◆|******|◆|\n"); 
					 	printf("         |◆|******|◆|        ☆ 反馈记录       请按 9        |◆|******|◆|\n"); 
					 	printf("         |◆|******|◆|        ☆ 退出系统       请按 x        |◆|******|◆|\n"); 
					 	printf("         |◆|******|◆|                                       |◆|******|◆|\n");
					 	printf("          ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
					    printf("\n#################################################################################\n");
					    printf("\n▓                          *******************************                    ▓\n");
					    printf("\n#################################################################################\n");
					 	printf("\n\n\t\t##请输入你的选择：");
                        scanf("%s", &choice2);
                        printf("\033[0m"); // 重置文本颜色
 
                        switch (choice2) {
                            case '1':
                                showDepartments();
                                break;
                            case '2':
                                viewRegistrationHistory(users[user_count - 1].username);
                                break;
                            case '3':
                                cancelAppointment(users[user_count - 1].username);
                                break;
                            case '4':
                                giveFeedback();
                                break;
                            case '5':
                                seeDoctor(users[user_count - 1].username);
                                break;
                            case '6':
                                makePayment(users[user_count - 1].username);
                                break;
                            case '7':
                            	hospitalmanagement(users[user_count - 1].username);
                                break;
                            case '8':
                            	location();
                            	break;
                            case '9':
                            	history();
                            	break;
                            case 'x':
                                loggedIn = 0;
                                break;
                            default:
							     printf("无效的选择，请重新输入。\n");
                         
                        	}
                	}
                }
                break;
            case '3':
                exit(0);
            default:
                printf("无效的选择，请重新输入。\n");
        }
    }
 
    return 0;
}
 
int registerUser() {
    printf("\n--- 用户注册 ---\n");
    printf("请输入用户名：");
    scanf("%s", users[user_count].username);
    printf("请输入密码：");
    scanf("%s", users[user_count].password);
    printf("请输入手机号：");
    scanf("%s", users[user_count].phone);
    printf("请输入身份证号：");
    scanf("%s", users[user_count].id_card);
 
    printf("注册成功！\n");
    user_count++;
 
    return 0;
}
int loginUser() {
    char username[20];
    char password[20];
 
    printf("\n--- 用户登录 ---\n");
    printf("请输入用户名：");
    scanf("%s", username);
    printf("请输入密码：");
    scanf("%s", password);
 
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("登录成功！\n");
            return 1; // 登录成功
        }
    }
 
    printf("用户名或密码错误，登录失败。\n");
    return 0; // 登录失败
}
 
void showDepartments() {
    printf("\n--- 科室列表 ---\n");
    printf("1. 急诊科\n2. 内科\n3. 外科\n4. 儿科\n5. 妇科\n6. 眼科\n7. 耳鼻喉科\n8. 口腔科\n9. 皮肤科\n");
 
    int departmentChoice;
    printf("请选择科室：");
    scanf("%d", &departmentChoice);
 
    char department[20];
 
    switch (departmentChoice) {
        case 1:
            strcpy(department, "急诊科");
            break;
        case 2:
            strcpy(department, "内科");
            break;
        case 3:
            strcpy(department, "外科");
            break;
        case 4:
            strcpy(department, "儿科");
            break;
        case 5:
            strcpy(department, "妇科");
            break;
        case 6:
            strcpy(department, "眼科");
            break;
        case 7:
            strcpy(department, "耳鼻喉科");
            break;
        case 8:
            strcpy(department, "口腔科");
            break;
        case 9:
            strcpy(department, "皮肤科");
            break;
        default:
            printf("无效的选择，请重新输入。\n");
            return;
    }
 
    showDoctors(department);
}
 
void showDoctors(char department[]) {
    printf("\n--- 医生列表 ---\n");
 
    for (int i = 0; i < doctor_count; i++) {
        if (strcmp(doctors[i].department, department) == 0) {
            printf("%d. %s (%s)\n", i + 1, doctors[i].name, doctors[i].is_specialist ? "专家" : "普通医生");
        }
    }
 
    int doctorChoice;
    printf("请选择医生（输入医生编号）：");
    scanf("%d", &doctorChoice);
 
    if (doctorChoice >= 1 && doctorChoice <= doctor_count) {
        int index = doctorChoice - 1;
        char time_slot[20];
 
        printf("请输入挂号时间段：");
        scanf("%s", time_slot);
 
        int result = makeAppointment(users[user_count - 1].username, time_slot);
        if (result == 1) {
            printf("挂号成功！\n");
            strcpy(registrations[registration_count].username, users[user_count - 1].username);
            strcpy(registrations[registration_count].doctor_name, doctors[index].name);
            strcpy(registrations[registration_count].department, doctors[index].department);
            strcpy(registrations[registration_count].time_slot, time_slot);
            registration_count++;
        } else {
            printf("挂号失败，选择的时间段已被预约。\n");
        }
    } else {
        printf("无效的选择，请重新输入。\n");
    }
}
 
int makeAppointment(char username[], char time_slot[20]) {
 
    // 检查是否有重复的挂号信息
    for (int i = 0; i < registration_count; i++) {
        if (strcmp(registrations[i].time_slot, time_slot) == 0) {
            return 0; // 挂号失败，选择的时间段已被预约
        }
    }
 
    return 1; // 挂号成功
}
 
int viewRegistrationHistory(char username[]) {
    printf("\n--- 挂号历史 ---\n");
    int found = 0;
    for (int i = 0; i < registration_count; i++) {
        if (strcmp(registrations[i].username, username) == 0) {
            printf("%d. 医生：%s，科室：%s，时间段：%s\n", i+1, registrations[i].doctor_name, registrations[i].department, registrations[i].time_slot);
            found = 1;
        }
    }
    if (!found) {
        printf("没有找到挂号记录。\n");
    }
    return found;
}

void cancelAppointment(char username[]) {
    printf("\n--- 取消预约 ---\n");
 
    viewRegistrationHistory(username);
 
    int cancelIndex;
    printf("请输入要取消的挂号序号：");
    scanf("%d", &cancelIndex);
 
    // 验证输入是否有效
    if (cancelIndex >= 1 && cancelIndex <= registration_count) {
        // 将序号转换为数组索引
        int i = cancelIndex - 1;

        // 找到匹配的挂号信息，进行取消
        for (int j = i; j < registration_count - 1; j++) {
            registrations[j] = registrations[j + 1];
        }
        registration_count--;

        printf("挂号取消成功！\n");
    } else {
        printf("无效的挂号序号。\n");
    }
}
    
void seeDoctor(char username[]) {
    printf("\n--- 看病 ---\n");
    int found = viewRegistrationHistory(username);
    if (!found) {
        return;
    }
    int registration_number; int random_number;
    printf("请输入挂号记录编号进行看病操作或输入0返回：");
    scanf("%d", &registration_number);
    if (registration_number == 0) {
        return;
    } else if (registration_number > 0 && registration_number <= registration_count) {
        printf("请描述你的症状：");
        scanf("%d", &random_number);
    } else {
        printf("无效的挂号记录编号。\n");
        return;
    }
    // 如果随机数大于10，建议病人住院治疗
    if (random_number > 10) {
        printf("建议病人住院治疗。");
        
        // 额外加上60元的费用
        for (int i = 0; i < payment_count; i++) {
            if (strcmp(payments[i].username, username) == 0) {
                payments[i].amount_due += 60.0;  // 加上60元
                return;  // 直接返回，不执行后续看病的逻辑
            }
        }

        // 如果用户还没有在缴费记录中，添加新的记录
        strcpy(payments[payment_count].username, username);
        payments[payment_count].amount_due = 60.0;
        payment_count++;

        return;  // 直接返回，不执行后续看病的逻辑
    }

    // 随机选择药品并输出信息，缴费逻辑保持不变
    int medicine_index = random_number % NUM_MEDICINES;
    Medicine prescribed_medicine = medicines[medicine_index];
    
    printf("根据您的症状，医生为您开出了以下药品：%s，价格：%.2f元\n", prescribed_medicine.name, prescribed_medicine.price);
    int fd = 0;
    
    for (int i = 0; i < payment_count; i++) {
        if (strcmp(payments[i].username, username) == 0) {
            payments[i].amount_due += prescribed_medicine.price;
            fd = 1;
            break;
        }
    }
    
    if (!fd) {
        strcpy(payments[payment_count].username, username);
        payments[payment_count].amount_due = prescribed_medicine.price;
        payment_count++;
    }
}

void makePayment(char username[]) {
    printf("\n--- 缴费 ---\n");

    // 查找用户待支付金额
    float amount_due = 0.0;
    for (int i = 0; i < payment_count; i++) {
        if (strcmp(payments[i].username, username) == 0) {
            amount_due = payments[i].amount_due;
            break;
        }
    }

    if (amount_due == 0.0) {
        printf("没有待支付的费用。\n");
        return;
    }

    float payment;
    printf("您的待支付金额为：%.2f元\n请输入支付金额：", amount_due);
    scanf("%f", &payment);

    if (payment >= amount_due) {
        printf("缴费成功，祝您身体健康！\n");
        // 清除待支付金额
        for (int i = 0; i < payment_count; i++) {
            if (strcmp(payments[i].username, username) == 0) {
                payments[i].amount_due = 0.0;
                break;
            }
        }
    } else {
        printf("支付金额不足，请重新支付。\n");
    }
}

void hospitalmanagement(char username[]) {
    int choice;

    while (1) {
        printf("\n--- 医院管理 ---\n");
        printf("1. 日常住宿\n");
        printf("2. 日常作息\n");
        printf("请选择操作 (1 或 2)，按任意键返回上一界面： ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n--- 日常住宿 ---\n");
                printf("每日饭菜费用：30元\n");
                printf("床费：30元\n");
                break;
            case 2:
                printf("\n--- 日常作息 ---\n");
                printf("早上：8:00 开放病人家属探亲\n");
                printf("中午：13:00 至 14:30为午休时间，禁止大声喧哗\n");
                printf("晚上：21:00 前，除特殊病人外，其他病人的家属\n");
                break;
            default:
                // 在退出前将缴费金额再加上60元
                for (int i = 0; i < payment_count; i++) {
                    if (strcmp(payments[i].username, username) == 0) {
                        payments[i].amount_due += 60.0;  // 加上60元
                        break;
                    }
                }
                return; // 任意键返回上一界面
        }

        // 按任意键返回上一界面
        printf("\n按任意键返回上一界面...\n");
        getchar(); // 捕获回车
        getchar(); // 捕获任意键
    }
}

void history() {
    printf("反馈历史记录:\n");
    int s,x,y;
    printf("1.挂号系统反馈记录:\n");
    printf("2.医生反馈记录:\n");
    scanf("%d",&s);
    if(s==1){
	 printf("1.挂号系统反馈记录\n");
	 x=1;
    while (x <m) {
        printf("%d:%s\n",x,history1[x].his1);x++;
   		}
    }
     if(s==2){printf("2.医生反馈记录:\n");
	 y=1;
    while (y <n) {
        printf("%d:%s\n",y,history2[y].his2);y++;
   		}
    }
    if(s!=1&&s!=2){printf("\n错误输入\n");
    }
}

void giveFeedback() {
    printf("\n--- 反馈和评价 ---\n");
    // 获取用户输入
    char a[20];
    printf("请选择反馈类型（1.挂号系统反馈 2.医生反馈）：");
    scanf("%s", a);
    // 根据用户选择输出不同的反馈提示
    if (strcmp(a, "1") == 0) {
        printf("您选择了挂号系统反馈\n");
        printf("请输入您的评价：");
        scanf("%s",&history1[m].his1);
        printf("您的评价是：%s\n，谢谢您的对挂号系统的反馈",history1[m].his1);m++;
    } else if (strcmp(a, "2") == 0) {
        printf("您选择了医生反馈\n");
        printf("请输入您的评价：");
        scanf("%s",&history2[n].his2);
        printf("您的评价是：%s\n，谢谢您的对医生的反馈",history2[n].his2);n++;
    } else {
        printf("无效的选项，请重新选择。\n");
    }
}

//导航功能
void location() {
	int num;
	printf("1. 急诊科\n2. 内科\n3. 外科\n4. 儿科\n5. 妇科\n6. 眼科\n7. 耳鼻喉科\n8. 口腔科\n9. 皮肤科\n");
	scanf("%d",&num);
    switch (num) {
        case 1:
            printf("地点：门诊部2f N202\n");
            break;
        case 2:
            printf("地点：门诊部1f N102\n");
            break;
        case 3:
            printf("地点：门诊部3f S303\n");
            break;
        case 4:
            printf("地点：门诊部3f N301\n");
            break;
        case 5:
            printf("地点：门诊部2f N202\n");
            break;
        case 6:
            printf("地点：门诊部2f N203\n");
            break;
        case 7:
            printf("地点：门诊部3f N308\n");
            break;
        case 8:
            printf("地点：门诊部5f S505\n");
            break;
        case 9:
            printf("地点：门诊部4f N401\n");
            break;
        default:
            printf("无效的输入！请输入1-9之间的数字。\n");
    }
}
