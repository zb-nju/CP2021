#include <assert.h>
#include <stdio.h>
int output_count = 0;
#define err_place 18
#define write(a)                         \
    {                                    \
        output_count++;                  \
        printf("%d\n", a);               \
        if (output_count == err_place) { \
            printf("here\n");            \
            assert(0);                   \
        }                                \
    }

int safe_add(int lhs_add, int rhs_add) {
    if ((((lhs_add > 0) && (rhs_add > 0) && (lhs_add > (2147483647 - rhs_add))) ||
         ((lhs_add < 0) && (rhs_add < 0) && (lhs_add < (-2147483648 - rhs_add))))) {
        return lhs_add;
    }
    return lhs_add + rhs_add;
}

int safe_sub(int lhs_sub, int rhs_sub) {
    if (((lhs_sub > 0) && (rhs_sub < 0) && (lhs_sub > 2147483647 + rhs_sub)) ||
        ((lhs_sub < 0) && (rhs_sub > 0) && (lhs_sub < -2147483648 + rhs_sub))) {
        return lhs_sub;
    }
    return lhs_sub - rhs_sub;
}

int safe_mul(int lhs_mul, int rhs_mul) {
    if ((((lhs_mul > 0) && (rhs_mul > 0) && (lhs_mul > (2147483647 / rhs_mul))) ||
         ((lhs_mul > 0) && (rhs_mul <= 0) && (rhs_mul < (-2147483648 / lhs_mul))) ||
         ((lhs_mul <= 0) && (rhs_mul > 0) && (lhs_mul < (-2147483648 / rhs_mul))) ||
         ((lhs_mul <= 0) && (rhs_mul <= 0) && (lhs_mul != 0) && (rhs_mul < (2147483647 / lhs_mul))))) {
        return lhs_mul;
    }
    return lhs_mul * rhs_mul;
}

int safe_div(int lhs_div, int rhs_div) {
    if (((rhs_div == 0) || ((lhs_div == -2147483648) && (rhs_div == (-1))))) {
        return lhs_div;
    }
    return lhs_div / rhs_div;
}

int safe_index(int i, int size) {
    if (i < 0 || i >= size) {
        return 0;
    }
    return i;
}

int i_func_36(int i_func_36_i_0, int i_func_36_i_1, int i_func_36_i_2, int i_func_36_i_3) {
    int i_L685;
    int i_L686;
    int i_L687;
    int i_L688;
    if (i_func_36_i_3 <= 0) {
        return -923667631;
    } else {
        i_func_36_i_3 = i_func_36_i_3 - 1;
    }

    i_L685 = i_func_36_i_0 = (i_func_36_i_1 || i_func_36_i_2);
    i_L686 = i_func_36_i_0 = (i_func_36_i_1 || i_func_36_i_2);
    i_L687 = i_func_36_i_0 = (i_func_36_i_1 && i_func_36_i_2);
    i_L688 = 0;
    i_func_36_i_3 = i_func_36_i_3 - 1;
    while (((i_func_36_i_0 = i_func_36(i_func_36_i_1, -879925251, i_func_36_i_2, i_func_36_i_3))) && (i_L688 < 4)) {
        int i_L689;
        int i_L690;
        int i_L691;
        int i_L692;
        i_func_36_i_3 = i_func_36_i_3 - 1;
        i_L689 = i_func_36((i_func_36_i_0 != i_func_36_i_1), (-1421510641 >= i_func_36_i_2), (i_L685 == i_L686),
                           i_func_36_i_3);
        i_L690 = i_func_36_i_0 = (i_func_36_i_1 || -1950582441);
        i_func_36_i_3 = i_func_36_i_3 - 1;
        i_L691 = i_func_36((i_func_36_i_0 != 2066139829), (!i_func_36_i_1), (i_func_36_i_2 - i_L685), i_func_36_i_3);
        i_L692 = 0;
        i_L688 = i_L688 + 1;
        while (((i_func_36_i_0 = safe_div(1914429428, i_func_36_i_1))) && (i_L692 < 4)) {
            int i_L693;
            int i_L694;
            int i_L695;
            i_func_36_i_3 = i_func_36_i_3 - 1;
            i_L693 = i_func_36_i_0 = i_func_36(i_func_36_i_1, i_func_36_i_2, i_L685, i_func_36_i_3);
            i_L694 = i_func_36_i_0 = safe_mul(i_func_36_i_1, i_func_36_i_2);
            i_func_36_i_3 = i_func_36_i_3 - 1;
            i_L695 = i_func_36_i_0 = i_func_36(i_func_36_i_1, i_func_36_i_2, i_L685, i_func_36_i_3);
            i_L692 = i_L692 + 1;
            i_func_36_i_0 = (i_func_36_i_1 = i_func_36_i_2);

            write(i_L693);
            write(i_L694);
            write(i_L695);
        }

        write(i_L689);
        write(i_L690);
        write(i_L691);
    }

    write(i_L685);
    write(i_L686);
    write(i_L687);
    i_func_36_i_3 = i_func_36_i_3 - 1;
    return i_func_36_i_0 = i_func_36(i_func_36_i_1, i_func_36_i_2, i_L685, i_func_36_i_3);
}

int i_func_37(int i_func_37_i_0) {
    int i_L698;
    int i_L699;
    int i_L697;
    int i_L700;
    int i_L701;
    int i_L696;
    int i_L702;
    int i_L703;
    int i_L704;
    int i_L708;
    if (i_func_37_i_0 <= 0) {
        return 168616373;
    } else {
        i_func_37_i_0 = i_func_37_i_0 - 1;
    }

    i_L698 = 232080530;
    i_L699 = -2068914731;
    i_L697 = i_L698 != i_L699;
    i_L700 = -950468098;
    i_L701 = 88879513;
    i_L696 = i_L697 = (i_L700 != i_L701);
    i_func_37_i_0 = i_func_37_i_0 - 1;
    i_L702 = i_L698 = i_func_36(i_L699, i_L697, i_L700, i_func_37_i_0);
    i_func_37_i_0 = i_func_37_i_0 - 1;
    i_L703 = i_L698 = i_func_36(i_L699, -580820008, 812009322, i_func_37_i_0);
    i_L704 = 0;
    i_L708 = 0;
    i_L698 = (1486909614 <= i_L699);
    i_func_37_i_0 = i_func_37_i_0 - 1;
    while ((i_func_37(i_func_37_i_0)) && (i_L704 < 4)) {
        int i_L705;
        int i_L706;
        int i_L707;
        i_func_37_i_0 = i_func_37_i_0 - 1;
        i_L705 = i_L698 = i_func_37(i_func_37_i_0);
        i_L706 = i_L698 = (i_L699 <= i_L697);
        i_L707 = i_L698 = i_L699;
        i_L704 = i_L704 + 1;
        i_L698 = (i_L699 >= i_L697);

        write(i_L705);
        write(i_L706);
        write(i_L707);
    }
    i_func_37_i_0 = i_func_37_i_0 - 1;
    while (((i_L698 = i_func_37(i_func_37_i_0))) && (i_L708 < 4)) {
        int i_L709;
        int i_L710;
        int i_L711;
        int i_L712;
        i_L709 = i_L698 = 374699819;
        i_L710 = i_L698 = -1750413999;
        i_L711 = i_L698 = (i_L699 != i_L697);
        i_L712 = 0;
        i_L708 = i_L708 + 1;
        i_L698 = 910700828;
        while (((i_L698 = (i_L699 = i_L697))) && (i_L712 < 4)) {
            int i_L713;
            int i_L714;
            int i_L715;
            i_L713 = i_L698 = (1908608129 / -1);
            i_L714 = i_L698 = (!i_L699);
            i_func_37_i_0 = i_func_37_i_0 - 1;
            i_L715 = i_func_37(i_func_37_i_0);
            i_L712 = i_L712 + 1;
            i_func_37_i_0 = i_func_37_i_0 - 1;
            i_L698 = i_func_36(i_L699, i_L697, i_L700, i_func_37_i_0);
            i_L698 = (i_L699 < i_L697);
            i_L698 = (i_L699 <= i_L697);

            write(i_L713);
            write(i_L714);
            write(i_L715);
        }
        i_L698 = (i_L699 <= i_L697);

        write(i_L709);
        write(i_L710);
        write(i_L711);
    }

    write(i_L698);
    write(i_L699);
    write(i_L697);
    write(i_L700);
    write(i_L701);
    write(i_L696);
    write(i_L702);
    write(i_L703);
    return i_L698 = i_L699;
}

int top_caller(int top_caller_i_33) {
    int i_L717;
    int i_L718;
    int i_L716;
    int i_L719;
    int i_L720;
    if (top_caller_i_33 <= 0) {
        return -819979237;
    } else {
        top_caller_i_33 = top_caller_i_33 - 1;
    }

    top_caller_i_33 = top_caller_i_33 - 1;
    i_L717 = top_caller(top_caller_i_33);
    i_L718 = 2064957737;
    i_L716 = i_L717 = (!i_L718);
    i_L719 = i_L717 = (i_L718 && i_L716);
    top_caller_i_33 = top_caller_i_33 - 1;
    i_L720 = i_L717 = i_func_37(top_caller_i_33);
    top_caller_i_33 = top_caller_i_33 - 1;
    i_L717 = top_caller(top_caller_i_33);

    write(i_L717);
    write(i_L718);
    write(i_L716);
    write(i_L719);
    write(i_L720);
    top_caller_i_33 = top_caller_i_33 - 1;
    return i_L717 = i_func_37(top_caller_i_33);
}

int main() {
    top_caller(10);
    return 0;
}
