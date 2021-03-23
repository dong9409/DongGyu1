$(document).ready(function() {
  $('#dataTable').DataTable({
  	lengthMenu: [10, 25, 50, 100],
  	lengthChange: false,
  	info: false,
  	searching: false,
  	ordering: false,
  	});
});