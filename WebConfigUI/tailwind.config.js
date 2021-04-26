module.exports = {
		purge: {
				enabled: process.env.PURGE_FILES == 1,
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
