module.exports = {
    purge: {
        enabled: true,
        content: ["./src/**/*.jsx", "./index.html"],
    },
    darkMode: false, // or 'media' or 'class'
    theme: {},
    variants: {
        extend: {
            backgroundColor: ["active"],
        },
    },
    plugins: [require('@tailwindcss/forms')],
};
