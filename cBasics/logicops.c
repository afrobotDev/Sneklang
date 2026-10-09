int can_access_registry(int is_premium, int reputation, int has_2fa) {
    if (is_premium == 1 || (reputation >= 100 && has_2fa == 1)) {
        return 1;
    } else {
        return 0;
    }
}
