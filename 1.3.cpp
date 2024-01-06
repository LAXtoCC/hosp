#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// ����ṹ�屣���û���Ϣ
typedef struct {
    char username[20];
    char password[20];
    char phone[15];
    char id_card[18];
} User;
 
// ����ṹ�屣��ҽ����Ϣ
typedef struct {
    char name[30];
    char department[20];
    int is_specialist; // 1: ר��ҽ����0: ��ͨҽ��
    float registration_fee;
} Doctor;
 
// ��ȫ�ֶ����������
const char* departments[] = {
    "�����", "�ڿ�", "���", "����", "����",
    "�ۿ�", "���Ǻ��", "��ǻ��", "Ƥ����"
};
const int NUM_DEPARTMENTS = sizeof(departments) / sizeof(departments[0]);
 
 
// ����ṹ�屣��Һ���Ϣ
typedef struct {
    char username[20];
    char doctor_name[30];
    char department[20];
    char time_slot[20];
} Registration;
 
// �������鱣���û���ҽ���͹Һ���Ϣ
User users[100];
Doctor doctors[20];
Registration registrations[100];
int user_count = 0;
int doctor_count = 0;
int registration_count = 0;
 
// ��������
int registerUser();
int loginUser();
void showDepartments();
void showDoctors(char department[]);
int makeAppointment(char username[], char time_slot[20]);
void viewRegistrationDetails(char username[]);
void viewRegistrationHistory(char username[]);
void cancelAppointment(char username[]);
void giveFeedback();
 
int main() {
    int choice;
    // �����ҽ����Ϣ��ר��ҽ���������п���
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        strcpy(doctors[doctor_count].name, "��ҽ��");
        strcpy(doctors[doctor_count].department, departments[i]);
        doctors[doctor_count].is_specialist = 1;
        doctors[doctor_count].registration_fee = 50.0;
        doctor_count++;
    }
    // �����ҽ����Ϣ����ͨҽ���������п���
    for (int i = 0; i < NUM_DEPARTMENTS; i++) {
        strcpy(doctors[doctor_count].name, "��ҽ��");
        strcpy(doctors[doctor_count].department, departments[i]);
        doctors[doctor_count].is_specialist = 0;
        doctors[doctor_count].registration_fee = 30.0;
        doctor_count++;
    }
 
    while (1) {
        printf("\n1. ע��\n2. ��¼\n3. �˳�\n��ѡ�������");
        scanf("%d", &choice);
 
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) {
                    int loggedIn = 1;
                    while (loggedIn) {
                        printf("\n1. ԤԼ�Һ�\n2. ��ѯ�Һ�\n3. ȡ��ԤԼ\n4. ����������\n5. �˳�\n��ѡ�������");
                        scanf("%d", &choice);
 
                        switch (choice) {
                            case 1:
                                showDepartments();
                                break;
                            case 2:
                                viewRegistrationHistory(users[user_count - 1].username);
                                break;
                            case 3:
                                cancelAppointment(users[user_count - 1].username);
                                break;
                            case 4:
                                giveFeedback();
                                break;
                            case 5:
                                loggedIn = 0;
                                break;
                            default:
                                printf("��Ч��ѡ�����������롣\n");
                        }
                    }
                }
                break;
            case 3:
                exit(0);
            default:
                printf("��Ч��ѡ�����������롣\n");
        }
    }
 
    return 0;
}
 
int registerUser() {
    printf("\n--- �û�ע�� ---\n");
    printf("�������û�����");
    scanf("%s", users[user_count].username);
    printf("���������룺");
    scanf("%s", users[user_count].password);
    printf("�������ֻ��ţ�");
    scanf("%s", users[user_count].phone);
    printf("���������֤�ţ�");
    scanf("%s", users[user_count].id_card);
 
    printf("ע��ɹ���\n");
    user_count++;
 
    return 0;
}
int loginUser() {
    char username[20];
    char password[20];
 
    printf("\n--- �û���¼ ---\n");
    printf("�������û�����");
    scanf("%s", username);
    printf("���������룺");
    scanf("%s", password);
 
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("��¼�ɹ���\n");
            return 1; // ��¼�ɹ�
        }
    }
 
    printf("�û�����������󣬵�¼ʧ�ܡ�\n");
    return 0; // ��¼ʧ��
}
 
void showDepartments() {
    printf("\n--- �����б� ---\n");
    printf("1. �����\n2. �ڿ�\n3. ���\n4. ����\n5. ����\n6. �ۿ�\n7. ���Ǻ��\n8. ��ǻ��\n9. Ƥ����\n");
 
    int departmentChoice;
    printf("��ѡ����ң�");
    scanf("%d", &departmentChoice);
 
    char department[20];
 
    switch (departmentChoice) {
        case 1:
            strcpy(department, "�����");
            break;
        case 2:
            strcpy(department, "�ڿ�");
            break;
        case 3:
            strcpy(department, "���");
            break;
        case 4:
            strcpy(department, "����");
            break;
        case 5:
            strcpy(department, "����");
            break;
        case 6:
            strcpy(department, "�ۿ�");
            break;
        case 7:
            strcpy(department, "���Ǻ��");
            break;
        case 8:
            strcpy(department, "��ǻ��");
            break;
        case 9:
            strcpy(department, "Ƥ����");
            break;
        default:
            printf("��Ч��ѡ�����������롣\n");
            return;
    }
 
    showDoctors(department);
}
 
void showDoctors(char department[]) {
    printf("\n--- ҽ���б� ---\n");
 
    for (int i = 0; i < doctor_count; i++) {
        if (strcmp(doctors[i].department, department) == 0) {
            printf("%d. %s (%s)\n", i + 1, doctors[i].name, doctors[i].is_specialist ? "ר��" : "��ͨҽ��");
        }
    }
 
    int doctorChoice;
    printf("��ѡ��ҽ��������ҽ����ţ���");
    scanf("%d", &doctorChoice);
 
    if (doctorChoice >= 1 && doctorChoice <= doctor_count) {
        int index = doctorChoice - 1;
        char time_slot[20];
 
        printf("������Һ�ʱ��Σ�");
        scanf("%s", time_slot);
 
        int result = makeAppointment(users[user_count - 1].username, time_slot);
        if (result == 1) {
            printf("�Һųɹ���\n");
            strcpy(registrations[registration_count].username, users[user_count - 1].username);
            strcpy(registrations[registration_count].doctor_name, doctors[index].name);
            strcpy(registrations[registration_count].department, doctors[index].department);
            strcpy(registrations[registration_count].time_slot, time_slot);
            registration_count++;
        } else {
            printf("�Һ�ʧ�ܣ�ѡ���ʱ����ѱ�ԤԼ��\n");
        }
    } else {
        printf("��Ч��ѡ�����������롣\n");
    }
}
 
int makeAppointment(char username[], char time_slot[20]) {
 
    // ����Ƿ����ظ��ĹҺ���Ϣ
    for (int i = 0; i < registration_count; i++) {
        if (strcmp(registrations[i].time_slot, time_slot) == 0) {
            return 0; // �Һ�ʧ�ܣ�ѡ���ʱ����ѱ�ԤԼ
        }
    }
 
    return 1; // �Һųɹ�
}
 
void viewRegistrationHistory(char username[]) {
    printf("\n--- �Һ���ʷ ---\n");
 
    for (int i = 0; i < registration_count; i++) {
        if (strcmp(registrations[i].username, username) == 0) {
            printf("%d. ҽ����%s�����ң�%s��ʱ��Σ�%s\n", i+1, registrations[i].doctor_name, registrations[i].department, registrations[i].time_slot);
        }
    }
}

void cancelAppointment(char username[]) {
    printf("\n--- ȡ��ԤԼ ---\n");
 
    viewRegistrationHistory(username);
 
    int cancelIndex;
    printf("������Ҫȡ���ĹҺ���ţ�");
    scanf("%d", &cancelIndex);
 
    // ��֤�����Ƿ���Ч
    if (cancelIndex >= 1 && cancelIndex <= registration_count) {
        // �����ת��Ϊ��������
        int i = cancelIndex - 1;

        // �ҵ�ƥ��ĹҺ���Ϣ������ȡ��
        for (int j = i; j < registration_count - 1; j++) {
            registrations[j] = registrations[j + 1];
        }
        registration_count--;

        printf("�Һ�ȡ���ɹ���\n");
    } else {
        printf("��Ч�ĹҺ���š�\n");
    }
}
 
void giveFeedback() {
    printf("\n--- ���������� ---\n");
    // ��ȡ�û�����
    char assessment[100];
    printf("��ѡ�������ͣ�1.�Һ�ϵͳ���� 2.ҽ����������");
    scanf("%s", assessment);
    // �����û�ѡ�������ͬ�ķ�����ʾ
    if (strcmp(assessment, "1") == 0) {
        printf("��ѡ���˹Һ�ϵͳ����\n");
        printf("�������������ۣ�");
        scanf("%s", assessment);
        printf("���������ǣ�%s\n��лл���ĶԹҺ�ϵͳ�ķ���", assessment);
    } else if (strcmp(assessment, "2") == 0) {
        printf("��ѡ����ҽ������\n");
        printf("�������������ۣ�");
        scanf("%s", assessment);
        printf("���������ǣ�%s\n��лл���Ķ�ҽ���ķ���", assessment);
    } else {
        printf("��Ч��ѡ�������ѡ��\n");
    }
}
