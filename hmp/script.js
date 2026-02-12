// ==================== GLOBAL VARIABLES ====================
const HOTEL_CONFIG = {
    name: 'Grand Horizon Hotel',
    maxRooms: 500,
    floors: 5,
    roomTypes: ['Single', 'Double', 'Deluxe', 'Suite']
};

// ==================== NAVIGATION FUNCTIONALITY ====================
document.addEventListener('DOMContentLoaded', function() {
    // Navbar scroll effect
    const navbar = document.getElementById('navbar');
    if (navbar) {
        window.addEventListener('scroll', function() {
            if (window.scrollY > 100) {
                navbar.classList.add('scrolled');
            } else {
                navbar.classList.remove('scrolled');
            }
        });
    }

    // Mobile menu toggle
    const hamburger = document.getElementById('hamburger');
    const navMenu = document.getElementById('navMenu');
    
    if (hamburger && navMenu) {
        hamburger.addEventListener('click', function() {
            navMenu.classList.toggle('active');
            
            // Animate hamburger
            const spans = hamburger.querySelectorAll('span');
            if (navMenu.classList.contains('active')) {
                spans[0].style.transform = 'rotate(45deg) translateY(8px)';
                spans[1].style.opacity = '0';
                spans[2].style.transform = 'rotate(-45deg) translateY(-8px)';
            } else {
                spans[0].style.transform = 'none';
                spans[1].style.opacity = '1';
                spans[2].style.transform = 'none';
            }
        });

        // Close menu when clicking on a link
        const navLinks = navMenu.querySelectorAll('.nav-link');
        navLinks.forEach(link => {
            link.addEventListener('click', function() {
                navMenu.classList.remove('active');
                const spans = hamburger.querySelectorAll('span');
                spans[0].style.transform = 'none';
                spans[1].style.opacity = '1';
                spans[2].style.transform = 'none';
            });
        });
    }

    // Smooth scroll for anchor links
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function(e) {
            const href = this.getAttribute('href');
            if (href !== '#' && href !== '') {
                e.preventDefault();
                const target = document.querySelector(href);
                if (target) {
                    target.scrollIntoView({
                        behavior: 'smooth',
                        block: 'start'
                    });
                }
            }
        });
    });

    // Contact form handling
    const contactForm = document.getElementById('contactForm');
    if (contactForm) {
        contactForm.addEventListener('submit', function(e) {
            e.preventDefault();
            alert('Thank you for your message! We will get back to you soon.');
            contactForm.reset();
        });
    }

    // Add animation on scroll
    observeElements();
});

// ==================== INTERSECTION OBSERVER FOR ANIMATIONS ====================
function observeElements() {
    const observerOptions = {
        threshold: 0.1,
        rootMargin: '0px 0px -100px 0px'
    };

    const observer = new IntersectionObserver(function(entries) {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                entry.target.style.opacity = '1';
                entry.target.style.transform = 'translateY(0)';
            }
        });
    }, observerOptions);

    // Observe elements with animation classes
    const animatedElements = document.querySelectorAll('.room-card, .service-card, .stat-item');
    animatedElements.forEach(el => {
        el.style.opacity = '0';
        el.style.transform = 'translateY(30px)';
        el.style.transition = 'opacity 0.6s ease, transform 0.6s ease';
        observer.observe(el);
    });
}

// ==================== VALIDATION UTILITIES ====================
function validateEmail(email) {
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailRegex.test(email);
}

function validatePhone(phone) {
    const phoneRegex = /^[\d\s\-\+\(\)]{10,}$/;
    return phoneRegex.test(phone);
}

function validatePassword(password) {
    return password.length >= 6;
}

function validateName(name) {
    return name.trim().length >= 2;
}

// ==================== LOCAL STORAGE UTILITIES ====================
const StorageManager = {
    // Get all users
    getUsers: function() {
        return JSON.parse(localStorage.getItem('hotelUsers') || '[]');
    },
    
    // Add new user
    addUser: function(user) {
        const users = this.getUsers();
        users.push(user);
        localStorage.setItem('hotelUsers', JSON.stringify(users));
    },
    
    // Find user by email
    findUserByEmail: function(email) {
        const users = this.getUsers();
        return users.find(u => u.email === email);
    },
    
    // Get all rooms
    getRooms: function() {
        return JSON.parse(localStorage.getItem('hotelRooms') || '[]');
    },
    
    // Update rooms
    updateRooms: function(rooms) {
        localStorage.setItem('hotelRooms', JSON.stringify(rooms));
    },
    
    // Get all bookings
    getBookings: function() {
        return JSON.parse(localStorage.getItem('hotelBookings') || '[]');
    },
    
    // Add new booking
    addBooking: function(booking) {
        const bookings = this.getBookings();
        bookings.push(booking);
        localStorage.setItem('hotelBookings', JSON.stringify(bookings));
    },
    
    // Get current user
    getCurrentUser: function() {
        return JSON.parse(localStorage.getItem('currentUser') || 'null');
    },
    
    // Set current user
    setCurrentUser: function(user) {
        localStorage.setItem('currentUser', JSON.stringify(user));
    },
    
    // Logout
    logout: function() {
        localStorage.removeItem('currentUser');
    }
};

// ==================== DATE UTILITIES ====================
const DateUtils = {
    // Format date to readable string
    formatDate: function(dateString) {
        const date = new Date(dateString);
        const options = { year: 'numeric', month: 'long', day: 'numeric' };
        return date.toLocaleDateString('en-US', options);
    },
    
    // Calculate nights between two dates
    calculateNights: function(checkIn, checkOut) {
        const start = new Date(checkIn);
        const end = new Date(checkOut);
        const diffTime = Math.abs(end - start);
        return Math.ceil(diffTime / (1000 * 60 * 60 * 24));
    },
    
    // Get today's date in YYYY-MM-DD format
    getTodayString: function() {
        return new Date().toISOString().split('T')[0];
    }
};

// ==================== ROOM UTILITIES ====================
const RoomUtils = {
    // Get room description based on type
    getRoomDescription: function(type) {
        const descriptions = {
            'Single': 'Perfect for solo travelers seeking comfort and style',
            'Double': 'Spacious accommodation for couples or friends',
            'Deluxe': 'Enhanced luxury with premium amenities',
            'Suite': 'The pinnacle of luxury and sophistication'
        };
        return descriptions[type] || 'Comfortable accommodation';
    },
    
    // Get room features based on type
    getRoomFeatures: function(type) {
        const features = {
            'Single': ['King Bed', '25m²', 'City View', 'Free WiFi', 'Minibar'],
            'Double': ['Two Beds', '35m²', 'Garden View', 'Free WiFi', 'Minibar', 'Balcony'],
            'Deluxe': ['King Bed', '45m²', 'Ocean View', 'Free WiFi', 'Minibar', 'Balcony', 'Living Area'],
            'Suite': ['Master Suite', '80m²', 'Panoramic View', 'Free WiFi', 'Full Kitchen', 'Jacuzzi', 'Living Room']
        };
        return features[type] || [];
    },
    
    // Get room capacity based on type
    getRoomCapacity: function(type) {
        const capacities = {
            'Single': 1,
            'Double': 2,
            'Deluxe': 2,
            'Suite': 4
        };
        return capacities[type] || 1;
    }
};

// ==================== SEARCH ALGORITHMS ====================
// Implementation of searching algorithms as required

// Linear Search - Find room by room number
function linearSearchRoom(rooms, roomNumber) {
    for (let i = 0; i < rooms.length; i++) {
        if (rooms[i].number === roomNumber) {
            return i; // Return index
        }
    }
    return -1; // Not found
}

// Binary Search - Find room by room number (requires sorted array)
function binarySearchRoom(rooms, roomNumber) {
    // First, sort rooms by number
    const sortedRooms = [...rooms].sort((a, b) => a.number - b.number);
    
    let left = 0;
    let right = sortedRooms.length - 1;
    
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        
        if (sortedRooms[mid].number === roomNumber) {
            return mid; // Return index in sorted array
        }
        
        if (sortedRooms[mid].number < roomNumber) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Not found
}

// ==================== SORTING ALGORITHMS ====================
// Implementation of sorting algorithms as required

// Bubble Sort - Sort rooms by price
function bubbleSortByPrice(rooms, ascending = true) {
    const arr = [...rooms];
    const n = arr.length;
    
    for (let i = 0; i < n - 1; i++) {
        for (let j = 0; j < n - i - 1; j++) {
            const condition = ascending ? 
                arr[j].price > arr[j + 1].price : 
                arr[j].price < arr[j + 1].price;
            
            if (condition) {
                // Swap
                [arr[j], arr[j + 1]] = [arr[j + 1], arr[j]];
            }
        }
    }
    
    return arr;
}

// Quick Sort - Sort rooms by type
function quickSortByType(rooms) {
    if (rooms.length <= 1) return rooms;
    
    const pivot = rooms[Math.floor(rooms.length / 2)];
    const left = rooms.filter(room => room.type < pivot.type);
    const middle = rooms.filter(room => room.type === pivot.type);
    const right = rooms.filter(room => room.type > pivot.type);
    
    return [...quickSortByType(left), ...middle, ...quickSortByType(right)];
}

// ==================== FORM UTILITIES ====================
function showErrorMessage(elementId, message) {
    const element = document.getElementById(elementId);
    if (element) {
        element.textContent = message;
        element.classList.add('show');
    }
}

function clearErrorMessages() {
    document.querySelectorAll('.error-message').forEach(el => {
        el.textContent = '';
        el.classList.remove('show');
    });
}

// ==================== NOTIFICATION SYSTEM ====================
const NotificationSystem = {
    show: function(message, type = 'info') {
        const notification = document.createElement('div');
        notification.className = `notification notification-${type}`;
        notification.textContent = message;
        notification.style.cssText = `
            position: fixed;
            top: 100px;
            right: 20px;
            background: ${type === 'success' ? '#27ae60' : type === 'error' ? '#e74c3c' : '#3498db'};
            color: white;
            padding: 1rem 2rem;
            border-radius: 4px;
            box-shadow: 0 5px 20px rgba(0,0,0,0.2);
            z-index: 10000;
            animation: slideInRight 0.3s ease;
        `;
        
        document.body.appendChild(notification);
        
        setTimeout(() => {
            notification.style.animation = 'slideOutRight 0.3s ease';
            setTimeout(() => notification.remove(), 300);
        }, 3000);
    }
};

// ==================== PRICE CALCULATOR ====================
function calculateBookingPrice(roomPrice, checkIn, checkOut) {
    const nights = DateUtils.calculateNights(checkIn, checkOut);
    const subtotal = roomPrice * nights;
    const tax = subtotal * 0.1; // 10% tax
    const total = subtotal + tax;
    
    return {
        nights: nights,
        subtotal: subtotal,
        tax: tax,
        total: total
    };
}

// ==================== EXPORT FOR USE IN OTHER FILES ====================
if (typeof module !== 'undefined' && module.exports) {
    module.exports = {
        HOTEL_CONFIG,
        StorageManager,
        DateUtils,
        RoomUtils,
        validateEmail,
        validatePhone,
        validatePassword,
        validateName,
        linearSearchRoom,
        binarySearchRoom,
        bubbleSortByPrice,
        quickSortByType,
        NotificationSystem,
        calculateBookingPrice
    };
}
