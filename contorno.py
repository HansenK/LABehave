import cv2

img = cv2.imread('img2.jpg', 0)
img = cv2.resize(img, (int(1836/5), int(3264/5)), interpolation=cv2.INTER_AREA)

blured = cv2.blur(img, (5, 5), 0)

(T, thresh) = cv2.threshold(blured, 50, 255, cv2.THRESH_BINARY)
edged = cv2.Canny(thresh, 30, 150)

(_, cnts, _) = cv2.findContours(edged.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
copia = img.copy()
cv2.drawContours(copia, cnts, -1, (255, 255, 255), 1)

cv2.imshow('imagem contorno', edged)
cv2.imshow('imagem real', img)


cv2.waitKey(0)
cv2.destroyAllWindows()